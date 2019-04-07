/*
 * coodinator.hpp
 *
 *  Created on: 6 Apr 2019
 *      Author: oruqimaru
 */

#pragma once

#include <ctime>
#include <thread>
#include <vector>
#include <string>
#include <cppkafka/include/cppkafka/configuration.h>
#include <fstream>
#include <ostream>
#include <set>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <cppkafka/include/cppkafka/message_builder.h>

#include "waker/waker.hpp"
#include "cppkafka/include/cppkafka/cppkafka.h"
#include "hnswlib/hnswalg.h"

using std::stringstream;
using std::pair;
using std::priority_queue;
using std::set;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

namespace dhnsw {
	long long getSysTime(){
		struct timeb t;
		ftime(&t);
		return 1000 * t.time + t.millitm;
	}

	const auto callback = [](const cppkafka::Topic&, const cppkafka::Buffer& key, int32_t partition_count) {
		// We'll convert the key into an int and perform modulo
		// over the amount of partitions
		std::srand((unsigned int) std::time(NULL));
		return std::rand() % partition_count;
	};

	class TaskMessage{
	private:
		int _query_id;
		vector<float> _query;
		long long _start_time;
	public:
		TaskMessage(int query_id, vector<float>& query){
			_start_time = getSysTime();
			_query.resize(query.size());
			std::copy(_query.begin(), _query.end(), query.begin());
			_query_id = query_id;
		}

		string toString(){
			stringstream ss;
			ss << _query_id  << " " << _start_time << " " << _query.size();
			for (int i = 0; i < _query.size(); i++){
				ss << " " << _query[i];
			}
			return ss.str();
		}
	};

	class Coordinator{
	private:
	    int _subhnsw_id;
	    int _process_id;
		int _wakeup_controller;
		int _data_dim;
		int _num_centroids;
		int _num_subhnsw;
		hnswlib::L2Space _l2space;
		hnswlib::HierarchicalNSW<float> _metahnsw;
		hnswlib::HierarchicalNSW<float>*	_subhnsw_addr;
        cppkafka::Producer _producer;
        vector<int> _map;

        void loadMap(string map_dir){
			ifstream i_file(map_dir);
			int num_centroids = 0;
			int num_subhnsw = 0;
			i_file >> num_centroids;
			i_file >> num_subhnsw;
			if (_num_centroids != num_centroids || _num_subhnsw != num_subhnsw){
				cout << "#[error ] map file wrong size" << endl;
				assert(0);
			}
			int buffer = 0;
			for (int i = 0; i < num_centroids; i++){
				i_file >> buffer;
				if (buffer < 0 || buffer >= num_subhnsw){
					cout << "#[error ] map file id out of range" << endl;
				}
				_map.push_back(buffer);
			}
		}

		cppkafka::Configuration modifyConfig(cppkafka::Configuration config){
			cppkafka::TopicConfiguration default_topic_config;
			default_topic_config.set_partitioner_callback(callback);
			config.set_default_topic_configuration(std::move(default_topic_config));
			return config;
        }
	public:
		Coordinator(int process_id, int hnsw_id, int vec_dim, int num_centroid, int num_subhnsw, int wakeup_controller, string subhnsw_dir, string meta_hnsw_dir, string map_dir, cppkafka::Configuration config):
		_subhnsw_id(hnsw_id),
		_process_id(process_id),
		_l2space(vec_dim),
		_metahnsw(&_l2space, meta_hnsw_dir),
		_data_dim(vec_dim),
		_wakeup_controller(wakeup_controller),
		_producer(modifyConfig(config)){
			_subhnsw_addr = new hnswlib::HierarchicalNSW<float>(&_l2space, subhnsw_dir);
			_num_centroids = num_centroid;
			_num_subhnsw = num_subhnsw;
			loadMap(map_dir);
		}

		void getWakeUpId(vector<float>& query, vector<int>& result){
			set<int> set;
			if (query.size() != _data_dim){
				cout << "#[error ] query wrong dimension" << endl;
				assert(0);
			}
			priority_queue<pair<float, long unsigned int > > knn = _metahnsw.searchKnn(query.data(), _wakeup_controller);
			for (int i = 0; i < _wakeup_controller; i++){
				set.insert(_map[(int) knn.top().second]);
				knn.pop();
			}
			result.resize(set.size());
			std::copy(set.begin(), set.end(), result.begin());
        }

        void produceTask(int query_id, vector<float>& query){
			vector<int> aim_subhnsw_id;
			getWakeUpId(query, aim_subhnsw_id);
			for (int i = 0; i < aim_subhnsw_id.size(); i++){
				string topic = "subhnsw_" + std::to_string(aim_subhnsw_id[i]);
				TaskMessage message(query_id, query);
				string key = "key";
				const string payload = message.toString();
				_producer.produce(cppkafka::MessageBuilder(topic.c_str()).key(key).payload(payload));

			}
        }
	};

}




