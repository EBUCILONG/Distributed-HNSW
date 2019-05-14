/*
 * coodinator.hpp
 *
 *  Created on: 6 Apr 2019
 *      Author: oruqimaru
 */

#pragma once

#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <set>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>


#include "dhnswlib/customer.hpp"
#include "dhnswlib/time.hpp"
#include "waker/waker.hpp"
#include "hnswlib/hnswalg.h"
#include "utils/binstream.hpp"

using husky::base::BinStream;
using std::stringstream;
using std::pair;
using std::priority_queue;
using std::set;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::chrono::steady_clock;

namespace dhnsw {

//	const auto callback = [](const cppkafka::Topic&, const cppkafka::Buffer& key, int32_t partition_count) {
//		// We'll convert the key into an int and perform modulo
//		// over the amount of partitions
//		std::srand((unsigned int) std::time(NULL));
//		return std::rand() % partition_count;
//	};

	class TaskMessage{
	public:
	    int _process_id;
        int _query_id;
        int _total_piece;
        vector<float> _query;
        long long _start_time;

	    TaskMessage(int vec_dim, string& input_string){
            vector<char> buffer(input_string.length());
            std::copy(input_string.c_str(), input_string.c_str() + input_string.length(), buffer.begin());
            BinStream bs(buffer);
            int size;
            float float_buffer;
            bs >> _process_id >> _query_id >> _total_piece >> size;
			if (vec_dim != size){
				cout << "#[error ] received task message query wrong length!" << endl;
				assert(0);
			}
//			bs >> float_buffer;
//			bs >> float_buffer;
            for (int i = 0; i < size; i++){
                bs >> float_buffer;
                _query.push_back(float_buffer);
            }
            bs >> _start_time;
	    }

		TaskMessage(int process_id, int query_id, int total_piece, int vec_dim, long long start_time, vector<float>& query):
		_process_id(process_id),
		_query(query){
	        if (query.size() != vec_dim){
	            cout << "#[error ] sending task message query wrong length!" << endl;
	            assert(0);
	        }
			_start_time = start_time;
			_query_id = query_id;
			_total_piece = total_piece;
		}

		string toString(){
            BinStream bs;
            bs << _process_id << _query_id << _total_piece << (int)_query.size();
            for(int i = 0; i < _query.size(); i++)
                bs << _query[i];
            bs << _start_time;
            return bs.to_string();
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
		hnswlib::HierarchicalNSW<float>* _metahnsw;
		cppkafka::Consumer _consumer;
        cppkafka::Producer _producer;
        vector<int> _map;

        void loadMap(string map_dir){
			ifstream i_file(map_dir);
			int num_centroids = 0;
			int num_subhnsw = 0;
			i_file >> num_subhnsw;
			i_file >> num_centroids;
			if (_num_centroids != num_centroids || _num_subhnsw != num_subhnsw){
				cout << "#[error ] map file wrong size with " << _num_centroids <<" "<<num_centroids<<" "<<
				_num_subhnsw << " " << num_subhnsw
				<< endl;
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
	public:
        hnswlib::HierarchicalNSW<float>* _subhnsw_addr;

		Coordinator(int process_id, int hnsw_id, int vec_dim, int num_centroid, int num_subhnsw, int wakeup_controller, string subhnsw_dir, string meta_hnsw_dir, string map_dir, cppkafka::Configuration producer_config, cppkafka::Configuration consumer_config, int meta_ef = 10, int sub_ef = 10):
		_subhnsw_id(hnsw_id),
		_process_id(process_id),
		_l2space(vec_dim),
		_data_dim(vec_dim),
		_wakeup_controller(wakeup_controller),
		_producer(producer_config),
		_consumer(consumer_config){
        	string topic = "query_t";
        	_consumer.subscribe({topic});
            _metahnsw = new hnswlib::HierarchicalNSW<float>(&_l2space, meta_hnsw_dir);
			_subhnsw_addr = new hnswlib::HierarchicalNSW<float>(&_l2space, subhnsw_dir);
			_num_centroids = num_centroid;
			_num_subhnsw = num_subhnsw;
			loadMap(map_dir);
			_subhnsw_addr->setEf(sub_ef);
			_metahnsw->setEf(meta_ef);
		}

        Coordinator(int process_id, int hnsw_id, int vec_dim, int num_centroid, int num_subhnsw, int wakeup_controller,  hnswlib::HierarchicalNSW<float>* subhnsw, hnswlib::HierarchicalNSW<float>* metahnsw, string map_dir, cppkafka::Configuration producer_config, cppkafka::Configuration consumer_config, int meta_ef = 10, int sub_ef = 10):
                _subhnsw_id(hnsw_id),
                _process_id(process_id),
                _l2space(vec_dim),
                _metahnsw(metahnsw),
                _subhnsw_addr(subhnsw),
                _data_dim(vec_dim),
                _wakeup_controller(wakeup_controller),
                _producer(producer_config),
                _consumer(consumer_config){
            string topic = "query_t";
            _consumer.subscribe({topic});
            _num_centroids = num_centroid;
            _num_subhnsw = num_subhnsw;
            loadMap(map_dir);
        }

        hnswlib::HierarchicalNSW<float>* getMetaGraph() {return _metahnsw;}

		void getWakeUpId(vector<float>& query, vector<int>& result){
			set<int> set;
			if (query.size() != _data_dim){
				cout << "#[error ] query wrong dimension" << endl;
				assert(0);
			}
			priority_queue<pair<float, long unsigned int > > knn = _metahnsw->searchKnn(query.data(), _wakeup_controller);
			for (int i = 0; i < _wakeup_controller; i++){
				set.insert(_map[(int) knn.top().second]);
				knn.pop();
			}
			result.resize(set.size());
			std::copy(set.begin(), set.end(), result.begin());
//        	for(int i = 0; i < 10; i++)
//        		result.push_back(i);
		}

		QueryMessage getQuery(){
			string string_msg;

			while (true) {
				cppkafka::Message msg = _consumer.poll();

				// Make sure we have a message before processing it
				if (msg) {
					if (msg.get_error()) {
						if (!msg.is_eof()) {
							cout << "#[error #] receive error message from kafka" << endl;
						}
						continue;
					} else {
//						_consumer.async_commit(msg);
						_consumer.store_offset(msg);
						string_msg = string(msg.get_payload());
						break;
					}
				}
			}

			return QueryMessage(_data_dim, string_msg);
		}

        void produceTask(int query_id, vector<float>& query, long long start_time){
			vector<int> aim_subhnsw_id;
			getWakeUpId(query, aim_subhnsw_id);
			for (int i = 0; i < aim_subhnsw_id.size(); i++){
				string topic("subhnsw_t_");
				topic = topic + std::to_string(aim_subhnsw_id[i]);
				TaskMessage message(_process_id, query_id, aim_subhnsw_id.size(), _data_dim, start_time, query);
				const string payload = message.toString();
				_producer.produce(cppkafka::MessageBuilder(topic.c_str()).payload(payload));
			}
        }

        void startWork(){
		    int counter = 0;
		    long long total_time = 0;
		    long long work_time = 0;
			long long start_time = get_current_time_milliseconds();
        	while(true){
        		QueryMessage msg = getQuery();
//        		long long work_start_time = get_current_time_nanoseconds();;
        		produceTask(msg.query_id_, msg.query_, msg.start_time_);
//        		long long end_time = get_current_time_milliseconds();
//                total_time += end_time - start_time;
//                start_time = end_time;
//                work_time += end_time - work_start_time;
//                counter++;
//				cout.setf(std::ios::right);
//                cout.width(10);
//                cout.fill(' ');
//                if(counter % 100 == 0) {
//                    cout << "[COOR] " << std::this_thread::get_id() << " " << (float) total_time / 100 << endl;
//                    total_time = 0;
//                }
        	}
        }
	};

}




