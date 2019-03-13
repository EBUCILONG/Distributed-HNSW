/*
 * waker.hpp
 *
 *  Created on: 12 Mar 2019
 *      Author: oruqimaru
 */
#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#include <set>
#include <math.h>

#include "utils/cluster.hpp"
#include "matrix.hpp"
#include "hnswlib/hnswalg.h"

using std::vector;
using sm::Point;
using sm::Cluster;
using std::cout;
using std::endl;

namespace sm {

	class Waker{
	private:
		vector<int> _wake_counter;
		int _num_cluster;
		vector<int> _map;
		vector<int> _wake_num;
		ss::Matrix<float>& _querys;
		hnswlib::HierarchicalNSW<float>& _hnsw;
	public:
		Waker(int num, const char* file, ss::Matrix<float>& querys, hnswlib::HierarchicalNSW<float>& hnsw):
			_querys(querys),
			_num_cluster(num),
			_hnsw(hnsw){
			_wake_counter.resize(10, 0);
			std::ifstream rFile(file);
			if(!rFile){
				cout << "#[error ] cannot open partition file from: " << file << endl;
				assert(false);
			}
			int label;
			while (rFile >> label)
				_map.push_back(label);
			if(_map.size() != _num_cluster){
				cout << "#[error ] partition file wrong size" <<endl;
				assert(false);
			}
		}

		vector<int> getMember(int label){
			vector<int> result;
			for (int i = 0; i < _num_cluster; i++){
				if ((int)_map[i] == label)
					result.push_back(i);
			}
			return result;
		}

		vector<int>* getWakeNum(){
			return &_wake_num;
		}

		int getNumCluster(){
			return _num_cluster;
		}

		void reset_wake_num(){
			_wake_num.resize(0);
		}

		vector<int> wakeUp(int index, int k){
			if (index > _querys.getSize()){
				cout << "#[error ] too big index in waker" << endl;
				assert(false);
			}
			std::priority_queue<std::pair<float, long unsigned int > > result = _hnsw.searchKnn(_querys[index], k);
			std::set<int> set;
			for (int i = 0; i < result.size(); i++){
				set.insert(_map[(int) result.top().second]);
				_wake_counter[_map[(int) result.top().second]]++;
				result.pop();
			}
			vector<int> waker;
			std::copy(set.begin(), set.end(), waker.begin());
			return waker;
		}

		int getWaker(std::priority_queue<std::pair<float, long unsigned int > >& result){
			std::set<int> set;
			for (int i = 0; i < result.size(); i++){
				set.insert(_map[(int) result.top().second]);
				_wake_counter[_map[(int) result.top().second]]++;
				result.pop();
			}
			return set.size();
		}

		void testWake (int k){
			reset_wake_num();
			for (int i = 0; i < _querys.getSize(); i++){
				std::priority_queue<std::pair<float, long unsigned int > > result = _hnsw.searchKnn(_querys[i], k);
				_wake_num.push_back(getWaker(result));
			}
		}

		vector<int>* getWakeCounter(){
			return &_wake_counter;
		}

		float getAverWake(){
			float result = 0;
			for (int i = 0; i < _wake_num.size(); i++)
				result +=  _wake_num[i];
			return result / _wake_num.size();
		}

		float getStdWake(){
			float ave = getAverWake();
			float result = 0;
			for (int i = 0; i < _wake_num.size(); i++)
				result +=  (_wake_num[i] - ave) * (_wake_num[i] - ave);
			return std::sqrt(result / _wake_num.size());
		}

	};

}


