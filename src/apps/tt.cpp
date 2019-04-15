//
// Created by Oruqimaru on 16/4/2019.
//

#include "distributed/partition.hpp"
#include "parameters.hpp"
#include "dhnsw_executor.hpp"
#include "executor.hpp"

int main(int argc, char** argv){
    ss::parameter para;
    LoadOptions(argc, argv, para);
    ss::Matrix<float> query(para.query_data);
    for (int i = 0; i < query.getDim(); i++)
        cout << query[0][i] << " ";
}