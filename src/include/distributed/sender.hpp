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

#define TASK_TAG 0
#define DATA_DIMENSION 128

using std::vector;
using std::string;

namespace mt {

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
		hnswlib::L2Space _l2space;
		hnswlib::HierarchicalNSW<float> _hnsw;

		sm::Waker _waker;

		int _COM_INDEX;
		int _COM_WORKER_SIZE;
	public:
		Sender(int COM_INDEX, Matrix<float>& query, string hnsw_path, vector<vector<float> > centroids, mt::Partition& partition, int centroid_size, int num_cluster, int num_worker,int ef = 100):
			_query(query),
			_query_size(_query.getSize()),
			_COM_INDEX(COM_INDEX),
			_COM_WORKER_SIZE(num_worker){
			_l2space(centroid_size);
			_hnsw(&_l2space, hnsw_path);
			_hnsw.setEf(ef);
			if (_hnsw.max_elements_ != num_cluster){
				cout << "#[error ] sender constructor wrong cluster number" << endl;
				MPI_Abort(MPI_COMM_WORLD, 0);
			}
			_waker(num_cluster,_query, _hnsw, partition, centroids, _COM_WORKER_SIZE);
		}

		Sender(int COM_INDEX, Matrix<float>& query, vector<vector<float> >& centroids, mt::Partition& partition , int centroid_size, int num_cluster, int num_worker, int ef = 100):
			_query(query),
			_query_size(_query.getSize()),
			_COM_INDEX(COM_INDEX),
			_COM_WORKER_SIZE(num_worker){
			if (centroid_size != centroids[0].size()){
				cout << "#[error ] sender constructor wrong centroids data dimension" << endl;
				MPI_Abort(MPI_COMM_WORLD, 0);
			}
			_l2space(centroid_size);
			_hnsw(&_l2space, centroids.size(), 32, 500);
			for (int i = 0; i < centroids.size(); i++)
				_hnsw.addPoint(centroids[i].data(), i);
			_hnsw.setEf(ef);
			_waker(num_cluster,_query, _hnsw, partition, centroids, _COM_WORKER_SIZE);
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
