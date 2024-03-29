#pragma once

#include <ctime>
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
#include <algorithm>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>

#include "dhnswlib/time.hpp"
#include "dhnswlib/worker.hpp"
#include "dhnswlib/coordinator.hpp"
#include "dhnswlib/receiver.hpp"
#include "parameters.hpp"
#include "utils/util.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

namespace dhnsw {
    class BenchmarkEvaluator{
    private:
        int _n_queries;
        int _top_k;
        vector<vector<pair<float, int>>> _result;
        cppkafka::Consumer _consumer;
    public:
        explicit BenchmarkEvaluator(int n_queries, int top_k, const cppkafka::Configuration& config):
        _n_queries(n_queries), _consumer(config), _top_k(top_k) {
            _result.resize(n_queries);
            for (int i=0; i<n_queries; i++) _result[i].resize(top_k);
            vector<string> topics;
            topics.push_back("evaluation");
            _consumer.subscribe(topics);
        }

        vector<vector<pair<float, int>>> evaluate(long long& avg_time, vector<int>& id_get, int controller) {
            cout << "[EVAL] Evaluator started." << endl;
            cout << "[EVAL]\t# Received\t|\tAvg. Time\t" << endl;
            int counter = 0;
            long long total_time = 0;
            while (counter < controller) {
                // receive message
                ResultMessage* result_msg;
                bool ret = receiveAnswer(result_msg, _consumer, _top_k);
                if(!ret) continue;  // failed to receive msg
                else if(result_msg->_query_id >= _n_queries)
                    continue;
                else {
                    // msg received
                    vector<int> result_ids = result_msg->_result_ids;
                    vector<float> distance = result_msg->_dists;
                    id_get.push_back(result_msg->_query_id);
                    for(int i=0; i<result_msg->_top_k; i++) {
                        _result[result_msg->_query_id][i] = make_pair(distance[i], result_ids[i]);
                    }
                    // increment counter
                    long long this_time = result_msg->_end_time;
                    total_time += this_time - result_msg->_start_time;
                    counter++;
                    if (counter % 10 == 0) {
                        cout << "[EVAL]\t"<< counter << "\t|\t" << total_time / 10.0 << endl;
                        total_time = 0;
                    }

                    // free memory
                    delete result_msg;

                }
            }
            avg_time = (total_time) / _n_queries;
            cout << "[EVAL] All messages received." << endl;
            return _result;
        }
    };

    class ThroughputEvaluator{
    private:
        int _top_k;
        cppkafka::Consumer _consumer;
        ofstream _save_file;


    public:
        explicit ThroughputEvaluator(int top_k, const cppkafka::Configuration& config, string save_path):
            _consumer(config), _top_k(top_k) {
            _save_file.open(save_path);
            vector<string> topics;
            topics.push_back("evaluation");
            _consumer.subscribe(topics);
        }

        ~ThroughputEvaluator() {
            _save_file.close();
        }

        void log_answer(long long start_time, long long end_time) {
            _save_file << start_time << " " << end_time << endl;
        }

        void evaluate(int print_interval, vector<int> aim_hnsws, int delay_limit){
            cout << "[EVAL] Evaluator started." << endl;
            cout << "[EVAL]\t# Received\t|\tDelay. Time\t|\t" << endl;
            vector<long long> times;
            long long counter = 0;
            long long current_time;
//            for (int i = 0; i < 5000; i++){
//                cppkafka::Message msg = _consumer.poll();
//                if(!msg) continue;
//                if(msg.get_error()) {
//                    if (!msg.is_eof()) {
//                        // error
////                        cout << "[RECV] Some error occured when polling from kafka." << endl;
//                    }
//                    continue;
//                }
//                // a message is received
//                _consumer.store_offset(msg);
//            }
            while (true) {
                // receive message
                cppkafka::Message msg = _consumer.poll();
                if(!msg) continue;
                if(msg.get_error()) {
                    if (!msg.is_eof()) {
                        // error
//                        cout << "[RECV] Some error occured when polling from kafka." << endl;
                    }
                    continue;
                }
                // a message is received
                _consumer.store_offset(msg);
                const cppkafka::Buffer& msg_body = msg.get_payload();
                string msg_string = msg_body;
                dhnsw::ResultMessage rm(10, msg_string);
                current_time = get_current_time_nanoseconds();
                long long delay = rm._end_time - rm._start_time;
                bool aim = false;
                for (int i = 0; i < aim_hnsws.size(); i++){
                    for(int j = 0; j < rm._aim_hnsws.size(); j++){
                        if (aim_hnsws[i] == rm._aim_hnsws[j]){
                            aim = true;
                            break;
                        }
                    }
                    if (aim == true)
                        break;
                }
                if (aim == true && delay < delay_limit){
                    cout << "[EVAL]\t" << counter << "\t|\t" << delay<< endl;
                    times.push_back(delay);
                    counter++;
                }
                if (counter == print_interval)
                    break;
            }

            times.erase(times.begin(), times.begin()+4000);
            std::sort(times.begin(), times.end());
            cout << "[EVAL]: 90: " << times[times.size() / 10 * 9] << " 95: " <<  times[times.size() / 100 * 95] << " avg: " << dhnsw::avg(times) << endl;
        }

        void evaluate(int print_interval, bool delay){
            if (delay){
                cout << "[EVAL] Evaluator started." << endl;
                cout << "[EVAL]\t# Received\t|\tDelay. Time\t|\t" << endl;
                vector<long long> times;
                long long counter = 0;
                long long current_time;
//            for (int i = 0; i < 5000; i++){
//                cppkafka::Message msg = _consumer.poll();
//                if(!msg) continue;
//                if(msg.get_error()) {
//                    if (!msg.is_eof()) {
//                        // error
////                        cout << "[RECV] Some error occured when polling from kafka." << endl;
//                    }
//                    continue;
//                }
//                // a message is received
//                _consumer.store_offset(msg);
//            }
                while (true) {
                    // receive message
                    cppkafka::Message msg = _consumer.poll();
                    if(!msg) continue;
                    if(msg.get_error()) {
                        if (!msg.is_eof()) {
                            // error
//                        cout << "[RECV] Some error occured when polling from kafka." << endl;
                        }
                        continue;
                    }
                    // a message is received
                    _consumer.store_offset(msg);
                    const cppkafka::Buffer& msg_body = msg.get_payload();
                    string msg_string = msg_body;
                    dhnsw::ResultMessage rm(10, msg_string);
                    current_time = get_current_time_nanoseconds();
                    long long delay = rm._end_time - rm._start_time;
                    cout << "[EVAL]\t" << counter << "\t|\t" << delay<< endl;
                    if (delay <= 10000000){
                        counter++;
                        times.push_back(delay);
                    }
                    if (counter == print_interval)
                        break;
                }
                times.erase(times.begin(), times.begin()+4000);
                std::sort(times.begin(), times.end());
                cout << "[EVAL]: 90: " << times[times.size() / 10 * 9] << " 95: " <<  times[times.size() / 100 * 95] << " avg: " << dhnsw::avg(times) << endl;
            }
            else{
                long long start_time = get_current_time_milliseconds();
                long long counter = 0;

                while (true) {
                    // receive message
                    cppkafka::Message msg = _consumer.poll();
                    if(!msg) continue;
                    if(msg.get_error()) {
                        if (!msg.is_eof()) {
                            // error
//                        cout << "[RECV] Some error occured when polling from kafka." << endl;
                        }
                        continue;
                    }
                    // a message is received
                    _consumer.store_offset(msg);
                    const cppkafka::Buffer& msg_body = msg.get_payload();
                    string msg_string = msg_body;
                    dhnsw::ResultMessage rm(10, msg_string);
                    if (counter % print_interval == 0) {
                        cout << get_current_time_milliseconds() - start_time << endl;
                    }
                    counter++;
                }
            }
        }

        void evaluate(int print_interval) {
            assert(print_interval != 0);
            cout << "[EVAL] Evaluator started." << endl;
            cout << "[EVAL]\t# Received\t|\tAvg. Time\t|\t" << endl;
            long long counter = 0;
            long long total_time = 0;
            long long last_time = get_current_time_milliseconds();
            int total_wake = 0;
            while (true) {
                // receive message
                cppkafka::Message msg = _consumer.poll();
                if(!msg) continue;
                if(msg.get_error()) {
                    if (!msg.is_eof()) {
                        // error
//                        cout << "[RECV] Some error occured when polling from kafka." << endl;
                    }
                    continue;
                }
                // a message is received
                _consumer.store_offset(msg);
//                const cppkafka::Buffer& msg_body = msg.get_payload();
//                string msg_string = msg_body;
//                dhnsw::ResultMessage rm(10, msg_string);
//                vector<int> aim_hnsws = {0, 9};
//                bool aim = false;
//                for (int i = 0; i < aim_hnsws.size(); i++){
//                    for(int j = 0; j < rm._aim_hnsws.size(); j++){
//                        if (aim_hnsws[i] == rm._aim_hnsws[j]){
//                            aim = true;
//                            break;
//                        }
//                    }
//                    if (aim == true)
//                        break;
//                }
//                if (aim == true) {
                    counter++;
                    if (counter % print_interval == 0) {
                        long long this_time = get_current_time_milliseconds();
                        cout << "[EVAL]\t" << counter << "\t|\t" << (float) (this_time - last_time) / print_interval
                             << endl;
                        last_time = this_time;
                    }
//                }
            }
        }
    };
}