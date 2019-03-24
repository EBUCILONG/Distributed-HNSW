#pragma once

#include <mpi.h>
#include <unordered_map>
#include <queue>
#include "distributed/slave.hpp"
#include "mpi_executor.hpp"
#include "parameters.hpp"

using std::unordered_map;
using std::priority_queue;
using std::pair;
using std::vector;
using std::make_pair;

namespace mt {

    void receiveResultMessage(void* buffer, int msg_len);

    struct Answer {
        Answer(): n_slaves(0) {};
        int n_slaves;
        priority_queue<pair<float, int>> p_queue;
    };

    class Receiver {
        int _n_queries;        // for benchmarking & debug
        unordered_map<int, Answer> _query_map;
        vector<vector<pair<float, int>>> _result;

        void _insert_answers(priority_queue<pair<float, int>>& pq, int* index, float* dist) {
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
        explicit Receiver(int n_queries): _n_queries(n_queries) {
            _result.resize(n_queries);
        };

        vector<vector<pair<float, int>>> receive() {
            /* Starts the receiver. It will return result stack when all answers
                are received. */

            // main Loop for receiving message
            int ef = -1;
            while (_result.size() < _n_queries) {
                int msg_len = sizeof(mt::result_message);
                void* buffer = malloc(msg_len);
                mt::receiveResultMessage(buffer, msg_len);
                mt::result_message* result_msg = (mt::result_message*)buffer;

                Answer& answer = _query_map[result_msg->query_id];
                ef = result_msg->ef;
                // Add result into queue
                _insert_answers(answer.p_queue, result_msg->result_id, result_msg->dist);
                // Increment counter & check if received data from all slaves
                answer.n_slaves ++;
                if (answer.n_slaves == result_msg->num_wake_up) {
                    _commit_answers(answer.p_queue, result_msg->query_id);
                    _query_map.erase(result_msg->query_id);
                }
                free(buffer);
            }
            return _result;
        }

    };

}
