/*
 * evaluate_tools.hpp
 *
 *  Created on: 1 May 2019
 *      Author: oruqimaru
 */

#pragma once

#include <iostream>
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

#include "dhnswlib/time.hpp"
#include "hnswlib/hnswalg.h"
#include "utils/util.hpp"
#include "matrix.hpp"

using std::pair;
using std::priority_queue;
using std::set;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

namespace eva{
	void test_wake_rate(const string& hnsw_path, const string& map_path, const string& query_path){
		ss::Matrix<float> query(query_path);
		vector<int> map;

		int total_partition = dhnsw::load_partition_map(map_path, map);
		hnswlib::L2Space l2space(query.getDim());
		hnswlib::HierarchicalNSW<float> meta(&l2space, hnsw_path);
		assert(meta.max_elements_ == map.size());
		int sizer = query.getSize();

		vector<int> ks;
		for(int i = 1; i <= 10; i++)
			ks.push_back(10 * i);
//		for (int i = 1; i <= 8; i++)
//			efs.push_back(100 + 50 * i);

		cout << "k   avg   stv   time(us)   specific data" << endl;
		meta.setEf(100);
		for (int i = 0; i < ks.size(); i++){
			long long total_time = 0;
			vector<int> counter(total_partition, 0);
			for (int j = 0; j < sizer; j++){
				long long start_time = dhnsw::get_current_time_milliseconds();
				set<int> set;
				std::priority_queue<std::pair<float, long unsigned int > > result = meta.searchKnn(query[j], ks[i]);
				for(int k = 0; k < ks[i]; k++){
					set.insert(map[(int)result.top().second]);
					result.pop();
				}
				total_time += dhnsw::get_current_time_milliseconds() - start_time;
				for (std::set<int>::iterator it=set.begin(); it!=set.end(); ++it){
					counter[*it]++;
				}
			}
			cout << ks[i] << " "
				 << dhnsw::avg(counter) / query.getSize() << " "
	 			 << dhnsw::stv(counter) / query.getSize() << " "
	 			 << (float)total_time / (float)query.getSize() << " ";
			for (int j = 0; j < counter.size(); j++)
				cout << counter[j] << " ";
			cout << endl;
		}
	}
}
