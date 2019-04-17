//
// Created by Oruqimaru on 16/4/2019.
//

#include <vector>
#include <>

#include "executor.hpp"
#include "../include/parameters.hpp"
#include "../include/hnswlib/hnswalg.h"
#include "../include/matrix.hpp"

using std::set;
using hnswlib::HierarchicalNSW
using std::vector;

vector<int> wakeUp(int i, float* query, HierarchicalNSW<float>& hnsw, int controller){
    set<int> set;
    vector<int> result;
    hnsw.searchKnn()
}

int main(int argc, char** argv){
    ss::parameter para;
    LoadOptions(argc, argv, para);
    ss::Matrix queries(para.query_data);
    hnswlib::L2Space l2space(queries.getDim());
    HierarchicalNSW<float> meta(&l2space, para.hnsw_dir + "/hnsw_meta");
    meta.setEf(para.sender_ef);
    vector<HierarchicalNSW<float>* > sub_hnsws;
    for (int i = 0; i < 10; i++){
        HierarchicalNSW<float>* ptr = new HierarchicalNSW<float>(&l2space, para.hnsw_dir + "/hnsw_slave" + std::to_string(i));
        sub_hnsws.push_back(ptr);
    }
    for ()
}