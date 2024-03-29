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
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>

#include "waker/waker.hpp"
#include "hnswlib/hnswalg.h"
#include "dhnswlib/coordinator.hpp"

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
    class ResultMessage{
    public:
        int _query_id;
        int _total_piece;
        int _top_k;
        vector<int> _result_ids;
        vector<int> _aim_hnsws;
        vector<float> _dists;
        //vector<vector<float> > _result_datas;
        long long _start_time;
        long long _end_time;

        ResultMessage(int query_id, int total_piece, int top_k, long long start_time, long long end_time, vector<int>& aim_hnsws, vector<int>& result_ids, vector<float>& dists):
        _query_id(query_id),
        _total_piece(total_piece),
        _top_k(top_k),
        _aim_hnsws(aim_hnsws),
        _result_ids(result_ids),
        _dists(dists),
        _start_time(start_time),
        _end_time(end_time) {
            if (_top_k != _result_ids.size()){
                cout << "#[error ] sending result message wrong topk or vec size!" << endl;
                assert(0);
            }
        }

        ResultMessage(int top_k, string input_string){
            vector<char> buffer(input_string.length());
            std::copy(input_string.c_str(), input_string.c_str() + input_string.length(), buffer.begin());
            BinStream bs(buffer);
            bs >> _query_id >> _total_piece >> _top_k;
            int id_buffer = 0;
            float dist_buffer = 0;
            if (_top_k != top_k){
                cout << "#[error ] received result message wrong topK!" << endl;
                assert(0);
            }

            for (int i = 0; i < _top_k; i++){
                bs >> id_buffer;
                _result_ids.push_back(id_buffer);
            }
            for (int i = 0; i < _top_k; i++){
                bs >> dist_buffer;
                _dists.push_back(dist_buffer);
            }
            int aim_size = 0;
            bs >> aim_size;
            for (int i = 0; i < aim_size; i++){
                bs >> id_buffer;
                _aim_hnsws.push_back(id_buffer);
            }
            bs >> _start_time;
            bs >> _end_time;
        }

        string toString(){
            BinStream bs;
            bs << _query_id << _total_piece << _top_k;
            for (int i = 0; i < _top_k; i++)
                bs << _result_ids[i];
            for (int i = 0; i < _top_k; i++)
                bs << _dists[i];
            bs << (int) _aim_hnsws.size();
            for (int i = 0; i < _aim_hnsws.size(); i++)
                bs << _aim_hnsws[i];
            bs << _start_time;
            bs << _end_time;
            return bs.to_string();
        }
    };

    class Worker {
    private:
        int _top_k;
        int _subhnsw_id;
        int _data_dim;
        hnswlib::HierarchicalNSW<float>* _hnsw;
        cppkafka::Consumer _consumer;
        cppkafka::Producer _producer;
    public:
        Worker(int subhnsw_id, int top_k, int data_dim, hnswlib::HierarchicalNSW<float>* hnsw, cppkafka::Configuration consumer_config, cppkafka::Configuration producer_config):
        _data_dim(data_dim),
        _subhnsw_id(subhnsw_id),
        _top_k(top_k),
        _hnsw(hnsw),
        _consumer(consumer_config),
        _producer(producer_config){
            string topic("subhnsw_t_");
            topic =topic + std::to_string(_subhnsw_id);
            _consumer.subscribe({topic});
        }

        TaskMessage getTask(){
            string string_msg;

            while (true) {
                cppkafka::Message msg = _consumer.poll();

                // Make sure we have a message before processing it
                if (msg) {
                    if (msg.get_error()) {
                        if (!msg.is_eof()) {
//                            cout << "#[error #] receive error message from kafka" << endl;
                        }
                        continue;
                    } else {
                        _consumer.store_offset(msg);
                        string_msg = string(msg.get_payload());
                        break;
                    }
                }
            }

            return TaskMessage(_data_dim, string_msg);
        }

        ResultMessage solveTask(TaskMessage& task){
            priority_queue<pair<float, long unsigned int >> topk = _hnsw->searchKnn(task._query.data(), _top_k);
            vector<int> ids;
            vector<float> dists;
            for (int i = 0; i < _top_k; i++){
                ids.push_back((int) topk.top().second);
                dists.push_back(topk.top().first);
                topk.pop();
            }
            return ResultMessage(task._query_id, task._total_piece, _top_k, task._start_time, 0, task._aim_hnsws, ids, dists);
        }

        void startWork(){
            while(true) {
                TaskMessage task = getTask();
                ResultMessage result = solveTask(task);
//change receiver
                string topic("receiver_t_");
                topic = topic + std::to_string(task._process_id);
                const string payload = result.toString();
                while(true) {
                    try {
                        //change receiver
                        _producer.produce(cppkafka::MessageBuilder(topic.c_str()).payload(payload));
//                        _producer.produce(cppkafka::MessageBuilder(topic.c_str()).partition(task._process_id).payload(payload));
                    }
                    catch (cppkafka::HandleException error) {
                        _producer.poll();
                        continue;
                    }
                    break;
                }
            }
        }
    };



}
