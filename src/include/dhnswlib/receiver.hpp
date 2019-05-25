#pragma once

#include <unordered_map>
#include <queue>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>

#include "dhnswlib/time.hpp"
#include "dhnswlib/time.hpp"
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

    // takes an uninitialized result_msg pointer
    bool receiveAnswer(ResultMessage*& result_msg, cppkafka::Consumer& consumer, int top_k) {
        cppkafka::Message msg = consumer.poll();
        if(!msg) return false;
        if(msg.get_error()) {
            if (!msg.is_eof()) {
                // error
//                cout << "[RECV] Some error occured when polling from kafka." << endl;
            }
            return false;
        }
        // a message is received
        consumer.store_offset(msg);
        const cppkafka::Buffer& msg_body = msg.get_payload();
        string msg_string = msg_body;
        // deserialize content & return the object
        result_msg = new ResultMessage(top_k, msg_string);
        return true;
    }

    struct Answer {
        Answer(): n_slaves(0), start_time(0) {};
        int n_slaves;
        long long start_time;
        priority_queue<pair<float, int>> p_queue;
    };

    class Receiver {
        unordered_map<int, Answer> _query_map;
        cppkafka::Consumer _consumer;
        cppkafka::Producer _producer;
        int _top_k;

        void _insert_answers(priority_queue<pair<float, int>>& pq, vector<int>& index, vector<float>& dist) {
            /* Inserts candidate vectors into priority queue. An vector will be
                ignored if it is not in the top n results. */
            for (int i=0; i< _top_k; i++) {
                // Check if we should insert the vector
                if (pq.size() < _top_k || dist[i] < pq.top().first) {
                    if(pq.size() >= _top_k) pq.pop();
                    pq.push(make_pair(dist[i], index[i]));
                }
            }
        }

        void _commit_answers(priority_queue<pair<float, int>>& pq, int query_id) {
            /* Gets all elements from the priority queue, and sends a message to evaluator */
            vector<int> result_ids;
            vector<float> dists;
            while(!pq.empty()) {
                dists.push_back(pq.top().first);
                result_ids.push_back(pq.top().second);
                pq.pop();
            }
            ResultMessage result(query_id, _query_map[query_id].n_slaves, _top_k, _query_map[query_id].start_time, get_current_time_nanoseconds(), result_ids, dists);
            string topic = "evaluation";
            string payload = result.toString();
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

    public:
        explicit Receiver(int process_id, int top_k, const cppkafka::Configuration& consumer_config,
                const cppkafka::Configuration& producer_config):
                _consumer(consumer_config), _producer(producer_config), _top_k(top_k) {
            vector<string> topics;
            string topic_name = "receiver_t_";
            // string topic_name = "receiver_t_" + std::to_string(process_id);
            topics.push_back(topic_name);
            _consumer.subscribe(topics);
        };

        void receive() {
            /* Starts the receiver. */
            cout << "[RECV] receiver started." << endl;
            // main Loop for receiving message
            // deliberate endless loop
            while (true) {
                // receive message
                ResultMessage* result_msg;
                bool ret = receiveAnswer(result_msg, _consumer, _top_k);
                if(!ret) continue;  // failed to receive msg
                else {
                    // msg received
                    Answer& answer = _query_map[result_msg->_query_id];
                    answer.start_time = result_msg->_start_time;
                    // Add result into queue
                    _insert_answers(answer.p_queue, result_msg->_result_ids, result_msg->_dists);
                    // Increment counter & check if received data from all slaves
                    answer.n_slaves ++;
                    if (answer.n_slaves == result_msg->_total_piece) {
                        _commit_answers(answer.p_queue, result_msg->_query_id);
                        _query_map.erase(result_msg->_query_id);
//                        cout << "[RECV] Sent " << counter << " messages." << endl;
                    }
                    // free memory
                    delete result_msg;
                }
            }
        }

    };

}
