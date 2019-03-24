/*
 * sender.hpp
 *
 *  Created on: 21 Mar 2019
 *      Author: oruqimaru
 */


#pragma once

#include <vector>
#include <string>
#include <mpi.h>

#include "waker/waker.hpp"
#include "matrix.hpp"
#include "distributed/macro.h"

using std::vector;
using std::string;

namespace mt {

/*
 * void loadSubset(string subset_path){
			std::ifstream inFile(subset_path);
			inFile >> _subset_size;
			int buffer = 0;
			for (int i = 0; i < _subset_size; i++){
				inFile >> buffer;
				_subset.push_back(buffer);
			}
			inFile.close();
		}
 */

	void saveSubset(int index, vector<int>& subset, string subset_dir){
		std::ofstream oFile(subset_dir + "/slave" + std::to_string(index));
		oFile << subset.size() << endl;
		for (int i = 0; i < subset.size(); i++)
			oFile << subset[i] << " ";
		oFile.close();
	}

	void loadClusters(vector<vector<int> >& clusters, string cluster_file){
		std::ifstream inFile(cluster_file);
		int sizer = 0;
		inFile >> sizer;
		clusters.resize(sizer);
		for(int i = 0; i < sizer; i++){
			int index = 0;
			int size = 0;
			int buffer = 0;
			inFile >> index >> size;
			for (int j = 0; j < size; j++){
				inFile >> buffer;
				clusters[index].push_back(buffer);
			}
		}
		inFile.close();
	}

	void loadCentroids(vector<vector<float> >& centroids, string centroids_file){
		std::ifstream inFile(centroids_file);
		int sizer = 0;
		int dimension = 0;
		inFile >> sizer >> dimension;
		if (dimension != DATA_DIMENSION){
			cout << "#[error ] centroids wrong dimension" << endl;
			MPI_Abort(MPI_COMM_WORLD, 0);
		}
		centroids.resize(sizer);
		float buffer;
		for (int i = 0; i < sizer; i++){
			for (int j = 0; j < dimension; j++){
				inFile >> buffer;
				centroids[i].push_back(buffer);
			}
		}
		inFile.close();
	}

	int trainHNSW(hnswlib::HierarchicalNSW<float>& hnsw, vector<vector<float> >& centroids){
		for (int i = 0; i < centroids.size(); i++)
			hnsw.addPoint(centroids[i].data(), i);
	}

	typedef struct tm {
		int index;
		double start_time;
		int num_wake_up;
		float data[DATA_DIMENSION];
		int ef;
	} task_message;

	class Sender{
	private:
		ss::Matrix<float>& _query;
		int _query_size;
		int trainer;
		hnswlib::L2Space _l2space;
		hnswlib::HierarchicalNSW<float> _hnsw;

		int _COM_INDEX;
		int _COM_WORKER_SIZE;
	public:
		sm::Waker _waker;

		Sender(int COM_INDEX, ss::Matrix<float>& query, string hnsw_path, vector<vector<float> > centroids, mt::Partition& partition, int centroid_size, int num_cluster, int num_worker,int ef = 100):
			_query(query),
			_query_size(_query.getSize()),
			_COM_INDEX(COM_INDEX),
			_COM_WORKER_SIZE(num_worker),
            _l2space(centroid_size),
            _hnsw(&_l2space, hnsw_path),
            _waker(num_cluster,_query, _hnsw, partition, centroids, _COM_WORKER_SIZE){
			_hnsw.setEf(ef);
			if (_hnsw.max_elements_ != num_cluster){
				cout << "#[error ] sender constructor wrong cluster number" << endl;
				MPI_Abort(MPI_COMM_WORLD, 0);
			}
		}

		Sender(int COM_INDEX, ss::Matrix<float>& query, vector<vector<float> >& centroids, mt::Partition& partition , int centroid_size, int num_cluster, int num_worker, int ef = 100):
			_query(query),
			_query_size(_query.getSize()),
			_COM_INDEX(COM_INDEX),
			_COM_WORKER_SIZE(num_worker),
            _l2space(centroid_size),
            _hnsw(&_l2space, centroids.size(), 32, 500),
            trainer(trainHNSW(_hnsw, centroids)),
            _waker(num_cluster,_query, _hnsw, partition, centroids, _COM_WORKER_SIZE){
		    cout << "#[sender] Started to add points to hnsw." << endl;
			if (centroid_size != centroids[0].size()){
				cout << "#[error ] sender constructor wrong centroids data dimension" << endl;
				MPI_Abort(MPI_COMM_WORLD, 0);
			}
            cout << "#[sender] Finished adding points to hnsw, setting ef." << endl;
			_hnsw.setEf(ef);
            cout << "#[sender] Finished setting " << endl;
		}

		void saveHNSW(string path){
			_hnsw.saveIndex(path);
		}

		void makeTask(int index, vector<int>& destination, task_message& tm, double start_time, int ef = 100, int wake_rate_controller = 10){
			destination = _waker.wakeUp(index, 10);
			tm.index = index;
			memcpy(tm.data, _query[index], DATA_DIMENSION * sizeof(float));
			tm.start_time = start_time;
			tm.num_wake_up = destination.size();
			tm.ef = ef;
		}
	};


}
