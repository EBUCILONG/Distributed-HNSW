#include <iostream>
#include <vector>
#include <fstream>
#include "bench/bencher.hpp"

using std::vector;
using std::pair;
using std::string;
using std::cout;
using std::endl;

vector<vector<pair<float, int>>> readResultFile(string path) {
    std::ifstream fin(path);
    int num_query, k;
    fin >> num_query >> k;
    vector<vector<pair<float, int>>> result;
    result.reserve(num_query);
    for(int i=0; i<num_query; i++) {
        vector<pair<float, int>> inner_vec;
        inner_vec.reserve(k);
        for (int j = 0; i < k; j++) {
            int id;
            float dist;
            fin >> id >> dist;
            inner_vec.emplace_back(std::make_pair(dist, id));
        }
        result.push_back(inner_vec);
    }
    return result;
}

int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "Usage: [result file] [benchmark file]" << endl;
        exit(0);
    }
    string result_path(argv[1]);
    string ground_truth_path(argv[2]);
    Bencher truth_bench(ground_truth_path.c_str());
    vector<vector<pair<float, int>>> result = readResultFile(result_path);
    Bencher result_bench(result, false);
    cout << "recall: "<<  std::to_string(truth_bench.avg_recall(result_bench)) << endl;
    return 0;
}