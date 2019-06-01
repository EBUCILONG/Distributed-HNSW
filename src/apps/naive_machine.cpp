//
// Created by Oruqimaru on 17/5/2019.
//

#include "distributed/partition.hpp"
#include "parameters.hpp"
#include "dhnsw_executor.hpp"
#include "executor.hpp"

int main(int argc, char** argv){
    ss::parameter para;
    LoadOptions(argc, argv, para);
    dhnsw::dhnsw_execute(para, para.num_subhnsw);
}