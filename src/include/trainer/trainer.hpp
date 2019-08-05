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

#include "dhnswlib/time.hpp"
#include "hnswlib/hnswalg.h"
#include "utils/cluster.hpp"
#include "utils/util.hpp"
#include "matrix.hpp"
#include "hnswlib/space_ip.h"
#include "distributed/partition.hpp"

using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;

namespace dhnsw{
	std::vector<sm::Cluster*>* get_centroids(ss::Matrix<float>& data, int aim_partition, vector<vector<float> >& centroids,int iteration = 75, int bomber = 4){
        std::vector<sm::Cluster*>* clusters;
        clusters = sm::cluster_machine(data, aim_partition, iteration, bomber, centroids);
        return clusters;
    }

    void get_partition_map(int size, vector<int>& partition_map, vector<vector<int> >& clusters, vector<int>& map){
		partition_map.resize(size);
		std::set<int> set;
		int counter = 0;
		for (int i = 0; i < clusters.size(); i++){
			for (int j = 0; j < clusters[i].size(); j++){
				assert(clusters[i][j] < size && clusters[i][j] >= 0);
				partition_map[clusters[i][j]] = map[i];
				counter++;
				set.insert(clusters[i][j]);
			}
		}
		assert(set.size() == size);
	}

    int get_cluster(vector<vector<int> >& clusters, std::vector<sm::Cluster*>* readyList){
		int counter = 0;
		clusters.resize(readyList->size());
		for (int i = 0; i < readyList->size(); i++){
			for (int j = 0; j < readyList->operator[](i)->_datas.size(); j++){
				clusters[i].push_back(readyList->operator[](i)->_datas[j]->get_index());
				counter ++;
			}
		}
		return counter;
	}

	void save_cluster(vector<vector<int> >& clusters, string path){
		ofstream fout(path);
		fout << clusters.size() << "\n";
		for (int i = 0; i < clusters.size(); i++){
			fout << clusters[i].size();
			for (int j = 0; j < clusters[i].size(); j++){
				fout << " " << clusters[i][j];
			}
			fout << endl;
		}
		fout.close();
		cout << "[trainer]# cluster saved successfully in " + path << endl;
	}

	int load_cluster(vector<vector<int> >& clusters, string path){
		int counter = 0;
		ifstream fin(path);
		int size = 0;
		fin >> size;
		clusters.resize(size);
		for (int i = 0; i < size; i++){
			int edges = 0;
			int buffer;
			fin >> edges;
			counter += edges;
			for (int j = 0; j < edges; j++){
				fin >> buffer;
				clusters[i].push_back(buffer);
			}
		}
		cout << "[trainer]# cluster loaded successfully from " + path << endl;
	}

    void save_map (string out_path, vector<int>& map, int num_partition){
    	std::ofstream fout(out_path);
    	fout << num_partition << " " << map.size() << std::endl;
    	for (int i = 0; i < map.size(); i++)
    		fout << map[i] << " ";
    	fout.close();
    }

    void save_graph (int num_edges, vector<vector<int> >& graph, string path){
		ofstream fout(path);
		fout << num_edges << " " << graph.size() << "\n";
		for (int i = 0; i < graph.size(); i++){
			fout << graph[i].size();
			for (int j = 0; j < graph[i].size(); j++){
				fout << " " << graph[i][j];
			}
			fout << endl;
		}
		fout.close();
		cout << "[trainer]# graph saved successfully in " + path << endl;
	}
	//the return value indicate the num_edge needed by partition function
	int load_graph (vector<vector<int> >& graph, string path){
		int num_edges = 0;
		ifstream fin(path);
		fin >> num_edges;
		int size = 0;
		fin >> size;
		graph.resize(size);
		for (int i = 0; i < size; i++){
			int edges = 0;
			int buffer;
			fin >> edges;
			for (int j = 0; j < edges; j++){
				fin >> buffer;
				graph[i].push_back(buffer);
			}
		}
		cout << "[trainer]# graph loaded successfully from " + path << endl;
	}

    void save_centroids (string out_path, vector<vector<float> >& centroids){
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

//    void load_centroids(string in_path, vector<vector<float> >& centroids){
//		std::ifstream fin(in_path);
//		int dim = 0;
//		int size = 0;
//		fin >> dim;
//		fin >> size;
//		centroids.resize(size);
//		for (int i = 0; i < size; i++){
//			float buffer;
//			for (int j = 0; j < dim; j++){
//				fin >> buffer;
//				centroids.push_back(buffer);
//			}
//		}
//	}

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

    void single_machine_trainer(int dimension, int aim_num_subhnsw, string centroid_path, string map_path, string partition_map_path, string hnsw_path, string cluster_path, mt::Partition& partition){
		vector<vector<float> > centroids;
		vector<vector<int> > clusters;
		vector<vector<int> > graph;

		load_centroids(centroid_path, centroids);
		int size = load_cluster(clusters, cluster_path);
		hnswlib::L2Space l2space(dimension);
		hnswlib::HierarchicalNSW<float> meta(&l2space, hnsw_path);
		int num_edges = meta.getLevel0Graph(graph);
		cout << "here" << endl;
		vector<int> map = partition.getPartition(graph, centroids, num_edges, aim_num_subhnsw);
		cout << "now here" << endl;
		vector<int> partition_map;
		get_partition_map(size, partition_map, clusters, map);

		save_map(partition_map_path, partition_map,aim_num_subhnsw);
		save_map (map_path, map, aim_num_subhnsw);
	}

    void single_machine_trainer(int dimension, int aim_partition, int aim_num_subhnsw, string data_path, string centroid_path, string map_path, string partition_map_path, string hnsw_path, string partition_hnsw_path,string cluster_path, mt::Partition& partition, int hnsw_m, int hnsw_ef_cons){
		omp_set_num_threads(31);
    	ss::Matrix<float> data(data_path);
        hnswlib::L2Space l2space(data.getDim());

        dhnsw::MiliTimer miliTimer;
        miliTimer.update_time();

        vector<vector<float> > centroids;
        std::vector<sm::Cluster*>* readyList = get_centroids(data, aim_partition, centroids);
        assert(aim_partition == centroids.size());

        //NOTE:save centroids
		save_centroids (centroid_path, centroids);

        std::cout << "[trainer]# finish clustering using " << miliTimer.span_and_update() << " ms" << std::endl;
		vector<vector<int> > clusters;
		int cluster_size = get_cluster(clusters, readyList);
		//NOTE:save cluster
		save_cluster(clusters, cluster_path);
		assert(cluster_size == data.getSize());

        hnswlib::HierarchicalNSW<float> meta(&l2space, centroids.size(), hnsw_m, hnsw_ef_cons);
        for (int i = 0; i < 1; i++) {
            meta.addPoint((void *) centroids[i].data(), (size_t) i);
        }
#pragma omp parallel for
        for (int i = 1; i < centroids.size(); i++) {
            meta.addPoint((void *) centroids[i].data(), (size_t) i);
        }

		std::cout << "finish constructing meta graph using " << miliTimer.span_and_update() << " ms" << std::endl;
		//NOTE: save hnsw

		hnswlib::HierarchicalNSW<float> partition_hnsw(&l2space, data.getSize(), hnsw_m, hnsw_ef_cons);
		for (int i = 0; i < 1; i++) {
			partition_hnsw.addPoint((void *) data[i], (size_t) i);
		}
#pragma omp parallel for
		for (int i = 1; i < centroids.size(); i++) {
			partition_hnsw.addPoint((void *) data[i], (size_t) i);
		}
		std::cout << "finish constructing partition graph using " << miliTimer.span_and_update() << " ms" << std::endl;

        meta.saveIndex(hnsw_path);
		partition_hnsw.saveIndex(partition_hnsw_path);

		miliTimer.update_time();

        vector<vector<int> > graph;
        int num_edges = meta.getLevel0Graph(graph);
        vector<int> map = partition.getPartition(graph, centroids, num_edges, aim_num_subhnsw);
        std::cout << "partition use " << miliTimer.span_and_update() << " ms" << std::endl;

        vector<int> partition_map;
        assert(readyList->size() == aim_partition);
        get_partition_map(data.getSize(), partition_map, clusters, map);

        save_map(partition_map_path, partition_map,aim_num_subhnsw);
        save_map (map_path, map, aim_num_subhnsw);
    }

    void fvecs_hnsw_machine(ss::Matrix<float>& data, string hnsw_path, int hnsw_m = 32, int hnsw_ef = 100){
        hnswlib::InnerProductSpace l2space(data.getDim());
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

//	void idvecs_hnsw_machine(string& data_path, string hnsw_path, int hnsw_m = 32, int hnsw_ef = 100){
//		int dimension, size;
//		int counter = 0;
//		dhnsw::getIdvecsInfo(data_path, dimension,size);
//		cout << "#[trainer] matrix total size: " << size  <<" with dim: " << dimension << endl;
//		hnswlib::L2Space l2space(dimension);
//		hnswlib::HierarchicalNSW<float> hnsw(&l2space, size, hnsw_m, hnsw_ef);
//		std::set<int> set;
//		long long start_time = dhnsw::get_current_time_milliseconds();
//
//		for (int part = 0; part < total_part; part++){
//			ss::Matrix<float> data(data_path, part, total_part);
//			cout << "#[trainer] start to assert "<< part << " part" << endl;
//			for (int i = 0; i < 1; i++) {
//				hnsw.addPoint((void *) data[i], (size_t) data.id_[i]);
//			}
//#pragma omp parallel for
//			for (int i = 1; i < data.getSize(); i++) {
//				hnsw.addPoint((void *) data[i], (size_t) data.id_[i]);
//			}
//			counter += data.getSize();
//			for (int i = 0; i < data.getSize(); i++)
//				set.insert(data.id_[i]);
//			cout << "#[trainer] finish assert " << part << " part" << endl;
//		}
//		cout << "#[trainer] use " << dhnsw::get_current_time_milliseconds() - start_time << " miliseconds" << endl;
//		assert(counter == size);
//		assert(set.size() == size);
//		hnsw.saveIndex(hnsw_path);
//	}

    void idvecs_hnsw_machine(string& data_path, string hnsw_path, int total_part, int hnsw_m = 32, int hnsw_ef = 100){
    	int dimension, size;
    	int counter = 0;
    	dhnsw::getIdvecsInfo(data_path, dimension,size);
    	cout << "#[trainer] matrix total size: " << size  <<" with dim: " << dimension << endl;
        hnswlib::InnerProductSpace l2space(dimension);
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

