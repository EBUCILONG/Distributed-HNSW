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

#include "dhnswlib/time.hpp"
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
    int counter = 0;
    long long time_sum = 0;
    long long last_time = dhnsw::get_current_time_milliseconds();

    while(true) {
        customer.send_message(para.customer_send_intv);
        long long this_time = dhnsw::get_current_time_milliseconds();
        time_sum += this_time - last_time;
        last_time = this_time;
        if (counter % 10000 == 0){
            cout << "[CUST] " << (float) time_sum / 10000 << "per 10000" << endl;
            time_sum = 0;
        }
        counter++;
    }
}