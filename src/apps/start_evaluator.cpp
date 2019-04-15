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
            { "enable.auto.commit", false }
    };
    Bencher truth_bench(para.ground_truth.c_str());
    dhnsw::Evaluator evaluator(truth_bench.getQueries(), para.topK, evaluator_config);
    long long avg_time = 0;
    vector<vector<pair<float, int>>> result = evaluator.evaluate(avg_time);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            cout << result[i][j].second << " " << result[i][j].first << " ";
        }
        cout << endl;
    }
    Bencher current_bench(result, false);
    cout << "time || recall"<< endl << std::to_string(avg_time) + " " + std::to_string(truth_bench.avg_recall(current_bench)) << endl;
    return 0;
}

