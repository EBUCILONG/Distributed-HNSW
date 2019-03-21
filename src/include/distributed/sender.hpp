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

using std::vector;
using std::string;

namespace mt {



	class Sender{
	private:
		ss::Matrix<float>& _query;
		int _query_size;
		hnswlib::L2Space _l2space;
		hnswlib::HierarchicalNSW<float> _hnsw;

		sm::Waker _waker;

		int _COM_INDEX;
	public:
		Sender(int COM_INDEX, Matrix<float>& query, string hnsw_path, string partition_file, int centroid_size, int num_cluster):
			_query(query),
			_query_size(_query.getSize()),
			_COM_INDEX(COM_INDEX){
			_l2space(centroid_size);
			_hnsw(&_l2space, hnsw_path);
			_waker(num_cluster, partition_file.c_str(), _query, _hnsw);
		}

		Sender(int COM_INDEX, Matrix<float>& query, vector<vector<float> >& centroids, string partition_file, int centroid_size, int num_cluster):
			_query(query),
			_query_size(_query.getSize()),
			_COM_INDEX(COM_INDEX){
			_l2space(centroid_size);
			_hnsw(&_l2space, centroids.size(), 32, 500);
			for (int i = 0; i < centroids.size(); i++)
				_hnsw.addPoint(centroids[i].data(), i);
			//TODO: get partition file from the _waker
		}





	};


}
