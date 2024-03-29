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
#include <random>
#include <functional>
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

#include "hnswlib/space_ip.h"
#include "utils/calculator.hpp"
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
        vector<int> _aim_hnsws;
        long long _start_time;

	    TaskMessage(int vec_dim, string& input_string){
            vector<char> buffer(input_string.length());
            std::copy(input_string.c_str(), input_string.c_str() + input_string.length(), buffer.begin());
            BinStream bs(buffer);
            int size;
            int hnsw_size;
            float float_buffer;
            int int_buffer;
            bs >> _process_id >> _query_id >> _total_piece >> hnsw_size;

            for (int i = 0; i < hnsw_size; i++){
            	bs >> int_buffer;
            	_aim_hnsws.push_back(int_buffer);
            }

            bs >> size;
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

		TaskMessage(int process_id, int query_id, int total_piece, int vec_dim, long long start_time, vector<int>& aim_hnsws, vector<float>& query):
		_process_id(process_id),
		_aim_hnsws(aim_hnsws),
		_query(query){
	        if (query.size() != vec_dim){
	            cout << "#[error ] sending task m essage query wrong length!" << endl;
	            assert(0);
	        }
			_start_time = start_time;
			_query_id = query_id;
			_total_piece = total_piece;
		}

		string toString(){
            BinStream bs;
            bs << _process_id << _query_id << _total_piece << (int) _aim_hnsws.size();
            for(int i = 0; i < _aim_hnsws.size(); i++){
            	bs << _aim_hnsws[i];
            }
            bs << (int)_query.size();
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
		hnswlib::InnerProductSpace _ip_space;
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
		_ip_space(vec_dim),
		_data_dim(vec_dim),
		_wakeup_controller(wakeup_controller),
		_producer(producer_config),
		_consumer(consumer_config){
        	string topic = "query_t";
        	_consumer.subscribe({topic});
            _metahnsw = new hnswlib::HierarchicalNSW<float>(&_l2space, meta_hnsw_dir);
            cout << "[COOR] Loaded meta graph" << endl;
//			_subhnsw_addr = new hnswlib::HierarchicalNSW<float>(&_ip_space, subhnsw_dir);
			cout << _subhnsw_addr->max_elements_ << endl;
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
				_ip_space(vec_dim),
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

//			change ip
//			vector<float> norm_q;
//			norm_q.insert(norm_q.begin(), query.begin(), query.end());
//			float norm = ss::CalculateNorm<float>(norm_q.data(), query.size());
//			for (int i = 0; i < query.size(); i++){
//				norm_q[i] /= norm;
//			}


			if (query.size() != _data_dim){
				cout << "#[error ] query wrong dimension" << endl;
				assert(0);
			}
//			change ip
			priority_queue<pair<float, long unsigned int > > knn = _metahnsw->searchKnn(query.data(), _wakeup_controller);
//			priority_queue<pair<float, long unsigned int > > knn = _metahnsw->searchKnn(norm_q.data(), _wakeup_controller);
			for (int i = 0; i < _wakeup_controller; i++){
				set.insert(_map[(int) knn.top().second]);
				knn.pop();
			}
			result.resize(set.size());
			std::copy(set.begin(), set.end(), result.begin());
//        	for(int i = 0; i < 10; i++)
//        		result.push_back(i);
		}

//		QueryMessage getQuery(){
//			string string_msg;
//
//			while (true) {
//				cppkafka::Message msg = _consumer.poll();
//
//				// Make sure we have a message before processing it
//				if (msg) {
//					if (msg.get_error()) {
//						if (!msg.is_eof()) {
////							cout << "#[error #] receive error message from kafka" << endl;
//						}
//						continue;
//					} else {
////						_consumer.async_commit(msg);
//						_consumer.store_offset(msg);
//						string_msg = string(msg.get_payload());
//						break;
//					}
//				}
//			}
//
//			return QueryMessage(_data_dim, string_msg);
//		}

        QueryMessage getQuery(cppkafka::Message& msg){
            string string_msg;

            while (true) {
                msg = _consumer.poll();

                // Make sure we have a message before processing it
                if (msg) {
                    if (msg.get_error()) {
                        if (!msg.is_eof()) {
//							cout << "#[error #] receive error message from kafka" << endl;
                        }
                        continue;
                    } else {
//						_consumer.async_commit(msg);
//                        _consumer.store_offset(msg);
                        string_msg = string(msg.get_payload());
                        break;
                    }
                }
            }

            return QueryMessage(_data_dim, string_msg);
        }

        void produceTask(int query_id, vector<float>& query, long long start_time, int random_num, int num_subhnsw=0){
			vector<int> aim_subhnsw_id;
			if(num_subhnsw == 0) {
				getWakeUpId(query, aim_subhnsw_id);
			}
			else{
				for (int i = 0; i < 10; i++)
					aim_subhnsw_id.push_back(i);
			}

			TaskMessage message(random_num, query_id, aim_subhnsw_id.size(), _data_dim, start_time, aim_subhnsw_id, query);

			for (int i = 0; i < aim_subhnsw_id.size(); i++){
				string topic("subhnsw_t_");
				topic = topic + std::to_string(aim_subhnsw_id[i]);

				const string payload = message.toString();
				while(true) {
					try {
						_producer.produce(cppkafka::MessageBuilder(topic.c_str()).payload(payload));
					}
					catch (cppkafka::HandleException error) {
						_producer.poll();
						continue;
					}
					break;
				}
			}

        }

        void startWork(int num_subhnsw=0){
		    int counter = 0;
		    long long total_time = 0;
		    long long work_time = 0;
			long long start_time = get_current_time_milliseconds();
			int t_id = (int) std::hash<std::thread::id>()(std::this_thread::get_id());

			std::random_device rd;
			std::mt19937 mt(rd() + t_id);
			std::uniform_int_distribution<int> aim_receiver(0,39);

			while(true){
                cppkafka::Message mess;
        		QueryMessage msg = getQuery(mess);
        		msg.start_time_ = get_current_time_nanoseconds();
//        		long long work_start_time = get_current_time_nanoseconds();;
//change receiver
//        		produceTask(msg.query_id_, msg.query_, msg.start_time_, aim_receiver(mt), num_subhnsw);
	            produceTask(msg.query_id_, msg.query_, msg.start_time_, _process_id, num_subhnsw);
                _consumer.store_offset(mess);
	            // long long end_time = get_current_time_milliseconds();
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




