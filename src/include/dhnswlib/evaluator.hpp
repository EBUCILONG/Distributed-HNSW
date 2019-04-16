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
        int _top_k;
        vector<vector<pair<float, int>>> _result;
        cppkafka::Consumer _consumer;
    public:
        explicit Evaluator(int n_queries, int top_k, const cppkafka::Configuration& config):
        _n_queries(n_queries), _consumer(config), _top_k(top_k) {
            _result.resize(n_queries);
            for (int i=0; i<n_queries; i++) _result[i].resize(top_k);
            vector<string> topics;
            topics.push_back("evaluation");
            _consumer.subscribe(topics);
        }

        vector<vector<pair<float, int>>> evaluate(long long& avg_time) {
            cout << "[EVAL] Evaluator started." << endl;
            int counter = 0;
            long long total_time = 0;
            while (counter < _n_queries) {
                // receive message
                ResultMessage* result_msg;
                bool ret = receiveAnswer(result_msg, _consumer, _top_k);
                if(!ret) continue;  // failed to receive msg
                else {
                    // msg received
                    vector<int> result_ids = result_msg->_result_ids;
                    vector<float> distance = result_msg->_dists;
                    for(int i=0; i<result_msg->_top_k; i++) {
                        _result[result_msg->_query_id][i] = make_pair(distance[i], result_ids[i]);
                    }
                    // increment counter
                    total_time += get_current_time_milliseconds() - result_msg->_start_time;
                    cout << "[EVAL] total time: " << total_time << endl;
                    counter++;
                    // free memory
                    cout << "[EVAL] counter: " << counter << " , total: " << _n_queries << endl;
                    delete result_msg;
                }
            }
            avg_time = (total_time) / _n_queries;
            cout << "[EVAL] All messages received." << endl;
            return _result;
        }
    };
}