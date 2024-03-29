//
// Created by Oruqimaru on 20/5/2019.
//

#include <vector>
#include <string>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>
#include <dhnswlib/evaluator.hpp>

#include "executor.hpp"
#include "parameters.hpp"
#include "dhnswlib/customer.hpp"
#include "matrix.hpp"

using std::vector;
using std::string;

int main(int argc, char** argv){
    ss::parameter para;
    LoadOptions(argc, argv, para);
    cppkafka::Configuration evaluator_config = {
            { "metadata.broker.list", para.broker_list},
            { "group.id",  "evaluator_g"},
            { "enable.auto.commit", true },
            {"enable.auto.offset.store", false},
    };
//    Bencher truth_bench(para.ground_truth.c_str());
    dhnsw::ThroughputEvaluator evaluator(para.topK, evaluator_config, para.eval_log_path);
    evaluator.evaluate(para.eval_print_intv, para.load_cluster);
    return 0;
}