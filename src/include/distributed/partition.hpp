#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <mpi.h>

#include "utils/calculator.hpp"
#include "kahiplib/interface/kaHIP_interface.h"

using std::vector;
using std::cout;
using std::endl;

namespace mt{
	class Partition{
		int (* _weight_func)(float);

		static int inline _square_weight(float weight) {
			return int(weight*weight);
		}

		static int inline _power_weight(float weight) {
            return int(pow(1.01, weight));
        }

	public:
		explicit Partition(int mode) {
			if(mode == 0) _weight_func = _square_weight;
			else if(mode == 1) _weight_func = _power_weight;
			else {
				std::cout << "[#error] Unsupported partition mode " << mode << " ." << std::endl;
                MPI_Abort(MPI_COMM_WORLD, 0);
			}
		}

		vector<int> getPartition(vector<vector<int>>& graph, vector<vector<float>>& centroids, int n_edges, int n_parts) {
//            cout << "#[sender] inside getPartition" << endl;
            int n = graph.size();
            int m = n_edges;
            int dim = centroids[0].size();
            // malloc
            int* xadj = (int*)malloc(sizeof(int)*(n+1));
            int* adjncy = (int*)malloc(sizeof(int)*m);
            float* adjwgt_t = (float*)malloc(sizeof(float)*m);
            int* adjwgt = (int*)malloc(sizeof(int)*m);
            int* result_partition = (int*)malloc(sizeof(int)*n);
//            cout << "#[sender] inside getPartition after malloc" << endl;
            // check if successful
            if(!xadj || !adjncy || !adjwgt || !adjwgt_t) {
                std::cout << "#[error] Failed to allocate memory for graph file." << std::endl;
                MPI_Abort(MPI_COMM_WORLD, 0);
            }
            // fill in the arrays
//            cout << "#[sender] inside getPartition after pointer check" << endl;
            int pos_count = 0;
            float max_weight = -1;
            for(int i=0; i<n; i++) {
                int n_neighbours = graph[i].size();
                xadj[i] = pos_count;
                for(int j=0; j<n_neighbours; j++) {
                    // edge: i -> graph[i][j]
                    int edge_to = graph[i][j];
                    float distance = ss::EuclidDistance<float>(centroids[i].data(), centroids[edge_to].data(), dim);
                    adjncy[pos_count + j] = edge_to;
                    adjwgt_t[pos_count + j] = distance;
                    if (distance > max_weight) max_weight = distance;
                }
                pos_count += n_neighbours;
//                cout << "#[sender] pos_count" + std::to_string(pos_count) << endl;
            }
//            cout << "#[sender] inside getPartition after large loop" << endl;
            xadj[n] = pos_count;
//            cout << "#[sender] inside getPartition after fill in arrays" << endl;
            // inverse the weights
            for(int i=0;i<m;i++) adjwgt[i] = _weight_func(max_weight - adjwgt_t[i]);
//            cout << "#[sender] inside getPartition after weight inverse" << endl;
            // run kaffpa
            double imbalance = 0.03;
            int edge_cut = 0;
            kaffpa(&n, NULL, xadj, adjwgt, adjncy, &n_parts, &imbalance, true, 0, STRONG, &edge_cut, result_partition);
//            cout << "#[sender] inside getPartition after kaffpa" << endl;
            vector<int> result(result_partition, result_partition + n);
            // free all malloced arrays
            free(xadj);
            free(adjncy);
            free(adjwgt_t);
            free(adjwgt);
            free(result_partition);
//            cout << "#[sender] exiting getPartition" << endl;
            std::ofstream output("./map.txt");
            output << result.size() << endl;
            output << n_parts << endl;
            for (int i=0; i<result.size(); i++) output << result[i] << endl;
            return result;
		}
	};
}
