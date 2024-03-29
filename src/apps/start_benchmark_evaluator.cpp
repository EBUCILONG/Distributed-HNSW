//
// Created by Michael Jiang on 2019-04-15.
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
    Bencher truth_bench(para.ground_truth.c_str());
    dhnsw::BenchmarkEvaluator evaluator(truth_bench.getQueries(), para.topK, evaluator_config);
    long long avg_time = 0;
    vector<int> id_get;
    vector<vector<pair<float, int>>> result = evaluator.evaluate(avg_time, id_get, para.num_subhnsw);
//    for (int i = 0; i < result.size(); i++){
//        for (int j = 0; j < 10; j ++){
//            cout << result[i][j].second << " " << result[i][j].first << " ";
//        }
//        cout << endl;
//    }
    Bencher current_bench(result, false);
    cout << "time || recall"<< endl << std::to_string(avg_time) + " " + std::to_string(truth_bench.avg_recall(current_bench, id_get)) << endl;
    return 0;
}

