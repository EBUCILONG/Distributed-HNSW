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
#include "dhnswlib/coodinator.hpp"

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

    class Worker {
    private:
        int _top_k;
        int _subhnsw_id;
        hnswlib::HierarchicalNSW<float>* _hnsw;
        cppkafka::Consumer _consumer;
        cppkafka::Producer _producer;
        cppkafka::Configuration modifyConfig(cppkafka::Configuration config){
            cppkafka::TopicConfiguration default_topic_config;
            default_topic_config.set_partitioner_callback(callback);
            config.set_default_topic_configuration(std::move(default_topic_config));
            return config;
        }
    public:
        Worker(int subhnsw_id, int top_k, hnswlib::HierarchicalNSW<float>* hnsw, cppkafka::Configuration config):
        _subhnsw_id(subhnsw_id),
        _top_k(top_k),
        _hnsw(hnsw),
        _consumer(config),
        _producer(modifyConfig(config)){
            string topic("subhnsw_");
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
                            cout << "#[error #] receive error message from kafka" << endl;
                        }
                        continue;
                    } else {
                        _consumer.commit(msg);
                        string_msg = string((msg.get_payload()));
                        break;
                    }
                }
            }

            
        }
    };



}
