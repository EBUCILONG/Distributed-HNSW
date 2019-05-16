//
// Created by Oruqimaru on 22/4/2019.
//

#pragma once

#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <set>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cmath>

#include <omp.h>

#include "../dhnswlib/time.hpp"
#include "../hnswlib/hnswalg.h"
#include "../utils/cluster.hpp"
#include "../utils/util.hpp"
#include "../matrix.hpp"
#include "../distributed/partition.hpp"

using std::vector;
using std::string;

namespace dhnsw{
std::vector<sm::Cluster*>* get_centroids(ss::Matrix<float>& data, int aim_partition, vector<vector<float> >& centroids,int iteration = 75, int bomber = 4){
        std::vector<sm::Cluster*>* clusters;
        clusters = sm::cluster_machine(data, aim_partition, iteration, bomber, centroids);
        return clusters;
    }

    void save_map (string out_path, vector<int>& map, int num_partition){
    	std::ofstream fout(out_path);
    	fout << num_partition << " " << map.size() << std::endl;
    	for (int i = 0; i < map.size(); i++)
    		fout << map[i] << " ";
    	fout.close();
    }

    void save_graph (int num_edges, vector<vector<int> >& graph, string path){

	}

    void save_centroids (string out_path, vector<vector<float> > centroids){
    	std::ofstream fout(out_path);
    	int dim = centroids[0].size();
    	fout << centroids[0].size() << " " << centroids.size() << std::endl;
    	for (int i =0; i < centroids.size(); i++){
    		for (int j = 0; j < dim; j++)
    			fout << centroids[i][j] << " ";
    		fout << std::endl;
    	}
    	fout.close();
    }

    void binary_trainer(int dimension, string data_path, string centroid_path, string tree_path, string map_path, int aim_partition, int aim_num_subhnsw, mt::Partition& partition, int hnsw_m = 32, int hnsw_ef_cons = 100){
    	long long start_time = get_current_time_milliseconds();
    	int power = (int) std::round(std::log2((float)aim_partition));
    	vector<vector<float> > centroids;
    	vector<int> sizes;
    	vector<vector<float> > tree;
    	ss::Matrix<float> datas(data_path);
        hnswlib::L2Space l2space(datas.getDim());

    	sm::binary_cluster_machine(datas, power, centroids, sizes, tree);

    	hnswlib::HierarchicalNSW<float> meta(&l2space, centroids.size(), 32, 100);
    	omp_set_num_threads(32);

    	for (int i = 0; i < 1; i++) {
			meta.addPoint((void *) centroids[i].data(), (size_t) i);
		}
#pragma omp parallel for
		for (int i = 1; i < centroids.size(); i++) {
			meta.addPoint((void *) centroids[i].data(), (size_t) i);
		}

		std::cout << "finish constructing meta graph" << std::endl;
		vector<vector<int> > graph;
		int num_edges = meta.getLevel0Graph(graph);
		vector<int> map = partition.getPartition(graph, centroids, num_edges, aim_num_subhnsw);

		std::cout << "total time in millisecond " << get_current_time_milliseconds() - start_time << std::endl;

		vector <int> partition_sizes(aim_num_subhnsw, 0);

		for (int i = 0; i < map.size(); i++){
			partition_sizes[map[i]] += sizes[i];
		}

		for (int i = 0; i < aim_num_subhnsw; i++)
			std::cout << partition_sizes[i] << std::endl;

		save_map (map_path, map, aim_num_subhnsw);
    	save_centroids (centroid_path, centroids);
    	save_centroids (tree_path, tree);
    }

    void single_machine_trainer(int dimension, int aim_partition, int aim_num_subhnsw, string data_path, string centroid_path, string map_path, string partition_map_path,string hnsw_path, mt::Partition& partition, int hnsw_m, int hnsw_ef_cons){
    	long long start_time = get_current_time_milliseconds();
    	ss::Matrix<float> data(data_path);
        hnswlib::L2Space l2space(data.getDim());
        vector<vector<float> > centroids;
        std::vector<sm::Cluster*>* readyList = get_centroids(data, aim_partition, centroids);
        assert(aim_partition == centroids.size());
        std::cout << "finish clustering" << std::endl;

        hnswlib::HierarchicalNSW<float> meta(&l2space, centroids.size(), hnsw_m, hnsw_ef_cons);

        omp_set_num_threads(31);

        for (int i = 0; i < 1; i++) {
            meta.addPoint((void *) centroids[i].data(), (size_t) i);
        }
#pragma omp parallel for
        for (int i = 1; i < centroids.size(); i++) {
            meta.addPoint((void *) centroids[i].data(), (size_t) i);
        }
		meta.saveIndex(hnsw_path);
        std::cout << "finish constructing meta graph" << std::endl;
        vector<vector<int> > graph;
        int num_edges = meta.getLevel0Graph(graph);
        vector<int> map = partition.getPartition(graph, centroids, num_edges, aim_num_subhnsw);
        std::cout << "total time in milisecond " << get_current_time_milliseconds() - start_time << std::endl;

        int counter = 0;
        vector<int> partition_map(data.getSize());
        assert(readyList->size() == aim_partition);
        for (int i = 0; i < readyList->size(); i++){
        	for (int j = 0; j < readyList->operator [](i)->_datas.size(); j++){
        		assert(map[i] >= 0 && map[i] < aim_num_subhnsw);
        		partition_map[readyList->operator [](i)->_datas[j]->get_index()] = map[i];
        		counter ++;
        	}
        }
        if(counter != data.getSize()) {
        	cout << "[error]# counter != data size" << endl;
			assert(counter == data.getSize());
		}

        save_map(partition_map_path, partition_map,aim_num_subhnsw);
        save_map (map_path, map, aim_num_subhnsw);
        save_centroids (centroid_path, centroids);
    }

    void fvecs_hnsw_machine(ss::Matrix<float>& data, string hnsw_path, int hnsw_m = 32, int hnsw_ef = 100){
        hnswlib::L2Space l2space(data.getDim());
        hnswlib::HierarchicalNSW<float> partition(&l2space, data.getSize(), hnsw_m, hnsw_ef);
        for (int i = 0; i < 1; i++) {
			partition.addPoint((void *) data[i], (size_t) i);
		}
#pragma omp parallel for
		for (int i = 1; i < data.getSize(); i++) {
			partition.addPoint((void *) data[i], (size_t) i);
		}
		partition.saveIndex(hnsw_path);
    }

    void idvecs_hnsw_machine(string& data_path, string& hnsw_path, int total_part, int hnsw_m = 32, int hnsw_ef = 100){
    	int dimension, size;
    	int counter = 0;
    	dhnsw::getIdvecsInfo(data_path, dimension,size);
    	cout << "#[trainer] matrix total size: " << size  <<" with dim: " << dimension << endl;
        hnswlib::L2Space l2space(dimension);
        hnswlib::HierarchicalNSW<float> hnsw(&l2space, size, hnsw_m, hnsw_ef);
        std::set<int> set;
        long long start_time = dhnsw::get_current_time_milliseconds();

        for (int part = 0; part < total_part; part++){
        	ss::Matrix<float> data(data_path, part, total_part);
        	cout << "#[trainer] start to assert "<< part << " part" << endl;
        	for (int i = 0; i < 1; i++) {
				hnsw.addPoint((void *) data[i], (size_t) data.id_[i]);
			}
#pragma omp parallel for
			for (int i = 1; i < data.getSize(); i++) {
				hnsw.addPoint((void *) data[i], (size_t) data.id_[i]);
			}
			counter += data.getSize();
			for (int i = 0; i < data.getSize(); i++)
				set.insert(data.id_[i]);
			cout << "#[trainer] finish assert " << part << " part" << endl;
        }
        cout << "#[trainer] use " << dhnsw::get_current_time_milliseconds() - start_time << " miliseconds" << endl;
        assert(counter == size);
        assert(set.size() == size);
		hnsw.saveIndex(hnsw_path);
    }
}

