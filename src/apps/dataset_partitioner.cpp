/*
 * dataset_partitioner.cpp
 *
 *  Created on: 30 Apr 2019
 *      Author: oruqimaru
 */


#include "distributed/partition.hpp"
#include "mpi_executor.hpp"
#include "mpi_par.hpp"
#include "parameters.hpp"
#include "executor.hpp"

int main(int argc, char** argv){
    int provided, claimed;
    MPI_Init_thread( 0, 0, MPI_THREAD_MULTIPLE, &provided);
    std::cout << "provided" << provided;
    ss::parameter para;
    LoadOptions(argc, argv, para);
//    mt::mpiPartitioner(para);
    mt::smart_partitioner(para);
}

