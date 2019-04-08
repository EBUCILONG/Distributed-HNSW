#pragma once

#include <unordered_map>
#include <queue>
#include "cppkafka/include/cppkafka/consumer.h"
#include "cppkafka/include/cppkafka/configuration.h"
#include "dhnswlib/worker.hpp"
#include "dhnswlib/coordinator.hpp"
#include "parameters.hpp"

using std::unordered_map;
using std::priority_queue;
using std::pair;
using std::vector;
using std::make_pair;
using std::cout;
using std::endl;

namespace dhnsw {

    struct Answer {
        Answer(): n_slaves(0) {};
        int n_slaves;
        priority_queue<pair<float, int>> p_queue;
    };

    class Receiver {
        int _n_queries;                             // for benchmarking & debug
        unordered_map<int, Answer> _query_map;
        vector<vector<pair<float, int>>> _result;
        cppkafka::Consumer _consumer;

        // takes an uninitialized result_msg pointer
        bool _receive_answers(ResultMessage*& result_msg) {
            cppkafka::Message msg = _consumer.poll();
            if(!msg) return false;
            if(msg.get_error()) {
                if (!msg.is_eof()) {
                    // error
                    cout << "[RECV] Some error occured when polling from kafka." << endl;
                }
                return false;
            }
            // a message is received
            const cppkafka::Buffer& msg_body = msg.get_payload();
            string msg_string = msg_body;
            // deserialize content & return the object
            result_msg = new ResultMessage(TOPK, msg_string);
            return true;
        }

        void _insert_answers(priority_queue<pair<float, int>>& pq, vector<int>& index, vector<float>& dist) {
            /* Inserts candidate vectors into priority queue. An vector will be
                ignored if it is not in the top n results. */
            for (int i=0; i< TOPK; i++) {
                // Check if we should insert the vector
                if (pq.size() < TOPK || dist[i] < pq.top().first)
                    pq.push(make_pair(dist[i], index[i]));
            }
        }

        void _commit_answers(priority_queue<pair<float, int>>& pq, int query_id) {
            /* Gets all elements from the priority queue and commit them to result stack */
            vector<pair<float, int>> indexes;
            while(!pq.empty()) {
                indexes.push_back(pq.top());
                pq.pop();
            }
            _result[query_id] = indexes;
        }

    public:
        explicit Receiver(int n_queries, const cppkafka::Configuration& config, string topic_name):
        _n_queries(n_queries), _consumer(config) {
            _result.resize(n_queries);
            _consumer.subscribe(topic_name);
        };

        vector<vector<pair<float, int>>> receive(double& avg_time) {
            /* Starts the receiver. It will return result stack when all answers
                are received. */

            // main Loop for receiving message
            int counter = 0;
            long long total_time = 0;
            while (counter < _n_queries) {
                // receive message
                ResultMessage* result_msg;
                bool ret = _receive_answers(result_msg);
                if(!ret) continue;  // failed to receive msg
                else {
                    // msg received
                    Answer& answer = _query_map[result_msg->_query_id];
                    // Add result into queue
                    _insert_answers(answer.p_queue, result_msg->_result_ids, result_msg->_dists);
                    // Increment counter & check if received data from all slaves
                    answer.n_slaves ++;
                    if (answer.n_slaves == result_msg->_total_piece) {
                        _commit_answers(answer.p_queue, result_msg->_query_id);
                        _query_map.erase(result_msg->_query_id);
                        total_time += getSysTime() - result_msg->_start_time;
                        counter++;
                    }
                    // free memory
                    delete result_msg;
                }
            }
            avg_time = static_cast<double>(total_time) / _n_queries;
            return _result;
        }

    };

}
