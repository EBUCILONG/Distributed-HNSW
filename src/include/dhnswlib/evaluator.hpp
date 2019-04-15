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

#include "dhnswlib/time.hpp"
#include "dhnswlib/worker.hpp"
#include "dhnswlib/coordinator.hpp"
#include "dhnswlib/receiver.hpp"
#include "parameters.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace dhnsw {
    class Evaluator{
    private:
        int _n_queries;
        vector<vector<pair<float, int>>> _result;
        cppkafka::Consumer _consumer;
    public:
        explicit Evaluator(int n_queries, const cppkafka::Configuration& config):
        _n_queries(n_queries), _consumer(config) {
            _result.resize(n_queries);
            vector<string> topics;
            topics.push_back("evaluation");
            _consumer.subscribe(topics);
        }

        vector<vector<pair<float, int>>> evaluate(long long& avg_time) {
            int counter = 0;
            long long total_time = 0;
            while (counter < _n_queries) {
                // receive message
                ResultMessage* result_msg;
                bool ret = receiveAnswer(result_msg, _consumer);
                if(!ret) continue;  // failed to receive msg
                else {
                    // msg received
                    vector<int> result_ids = result_msg->_result_ids;
                    vector<float> distance = result_msg->_dists;
                    for(int i=0; i<result_msg->_top_k; i++) {
                        _result[result_msg->_query_id][i] = make_pair(distance[i], result_ids[i]);
                    }
                    // Increment counter & check if received data from all slaves
                    total_time += get_current_time_milliseconds() - result_msg->_start_time;
                    counter++;
                    // free memory
                    delete result_msg;
                }
            }
            avg_time = (total_time) / _n_queries;
            return _result;
        }
    };
}