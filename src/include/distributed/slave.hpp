/*
 * slave.hpp
 *
 *  Created on: 22 Mar 2019
 *      Author: oruqimaru
 */

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>

#include "hnswlib/hnswalg.h"
#include "distributed/sender.hpp"
#include "matrix.hpp"

using std::vector;
using std::string;
using std::priority_queue;
using std::pair;

#define TOPK 10

namespace mt {

	typedef struct rm{
		int result_id[TOPK];
		float dist[TOPK];
		int query_id;
		double start_time;
		int num_wake_up;
		int ef;
	} result_message;

	class Slave{
	private:
		ss::Matrix<float>& _datas;
		int _subset_size;
		vector<int> _subset;
		hnswlib::L2Space _l2space;
		hnswlib::HierarchicalNSW<float> _hnsw;
	public:
		Slave(ss::Matrix<float> datas, string hnsw_path, string subset_path, int ef = 10):
			_datas(datas){
			_l2space(datas.getDim());
			_hnsw(&_l2space, hnsw_path);
			_hnsw.setEf(ef);
			loadSubset(subset_path);
		}

		Slave(ss::Matrix<float> datas, string subset_path, int ef = 10):
			_datas(datas){
			loadSubset(subset_path);
			_l2space(datas.getDim());
			_hnsw(&_l2space, _subset.size(), 32, 500);
			for (int i = 0; i < _subset_size; i++)
				_hnsw.addPoint(_datas[_subset[i]], _subset[i]);
			_hnsw.setEf(ef);
		}

		/*typedef struct tm {
			int index;
			double start_time;
			int num_wake_up;
			float data[DATA_DIMENSION];
			int ef;
		} task_message;*/

		void makeResult(task_message& task, result_message& result){
			_hnsw.setEf(task.ef);
			priority_queue<pair<float, long unsigned int >> topk = _hnsw.searchKnn(task.data, TOPK);
			for (int i = 0; i < TOPK; i++){
				result.result_id[i] = (int) topk.top().second;
				result.dist[i] = topk.top().first;
				topk.pop();
			}
			result.ef = task.ef;
			result.num_wake_up = task.num_wake_up;
			result.query_id = task.index;
			result.start_time = task.start_time;
		}

		void saveHNSW(string path){
			_hnsw.saveIndex(path);
		}

		void loadSubset(string subset_path){
			std::ifstream inFile(subset_path);
			inFile >> _subset_size;
			int buffer = 0;
			for (int i = 0; i < _subset_size; i++){
				inFile >> buffer;
				_subset.push_back(buffer);
			}
		}
	};
}

