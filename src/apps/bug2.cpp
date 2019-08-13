//
// Created by Oruqimaru on 11/4/2019.
//
#include "distributed/partition.hpp"
#include "parameters.hpp"
#include "dhnsw_executor.hpp"
#include "executor.hpp"

int main(int argc, char** argv){
    int provided, claimed;
    MPI_Init_thread( 0, 0, MPI_THREAD_MULTIPLE, &provided);

    ss::parameter para;
    LoadOptions(argc, argv, para);
    dhnsw::dhnsw_execute(para, 10);
}