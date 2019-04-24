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

#include "../hnswlib/hnswalg.h"
#include "../utils/cluster.hpp"
#include "../matrix.hpp"
#include "../distributed/partition.hpp"

using std::vector;
using std::string;

namespace dhnsw{
    vector<vector<float> > get_centroids(ss::Matrix<float>& data, int aim_partition, int iteration = 75, int bomber = 4){
        std::vector<sm::Cluster*>* clusters;
        vector<vector<float> > centroids;
        clusters = sm::cluster_machine(data, aim_partition, iteration, bomber, centroids);
        return centroids;
    }

    void save_map (string out_path, vector<int>& map, int num_partition){
    	std::ofstream fout(out_path);
    	fout << num_partition << " " << map.size() << std::endl;
    	for (int i = 0; i < map.size(); i++)
    		fout << map[i] << " ";
    	fout.close();
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

    void binary_trainer(int dimension, string data_path, string centroid_path, int aim_partition){
    	int power = (int) std::round(std::log2((float)aim_partition));
    	vector<vector<float> > centroids;
    	ss::Matrix<float> datas(data_path);
    	sm::binary_cluster_machine(datas, power, centroids);
    	save_centroids (centroid_path, centroids);
    }

    void single_machine_trainer(int dimension, int aim_partition, int aim_num_subhnsw, string data_path, string centroid_path, string map_path, mt::Partition& partition, int hnsw_m, int hnsw_ef_cons){
        ss::Matrix<float> data(data_path);
        hnswlib::L2Space l2space(data.getDim());
        vector<vector<float> > centroids = get_centroids(data, aim_partition);
        std::cout << "finish clustering" << std::endl;

        hnswlib::HierarchicalNSW<float> meta(&l2space, centroids.size(), hnsw_m, hnsw_ef_cons);

        omp_set_num_threads(18);

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

        save_map (map_path, map, aim_num_subhnsw);
        save_centroids (centroid_path, centroids);
    }
}

