//
// Created by Oruqimaru on 15/4/2019.
//

#include <vector>
#include <string>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>

#include "executor.hpp"
#include "parameters.hpp"
#include "dhnswlib/customer.hpp"
#include "matrix.hpp"

using std::vector;
using std::string;

int main(int argc, char** argv){
    ss::parameter para;
    LoadOptions(argc, argv, para);
    ss::Matrix<float> queries(para.query_data);
    cppkafka::Configuration producer_config = {
            { "metadata.broker.list", para.broker_list},
//            { "queue.buffering.max.ms", 10},
//            {"fetch.wait.max.ms", 5},
    };
    dhnsw::Customer customer(para.num_subhnsw, queries, producer_config);
    while(true) customer.send_message(para.customer_send_intv);
}