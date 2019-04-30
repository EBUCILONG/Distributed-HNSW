/*
 * dataset_partitioner.cpp
 *
 *  Created on: 30 Apr 2019
 *      Author: oruqimaru
 */


#include "distributed/partition.hpp"
#include "mpi_executor.hpp"
#include "parameters.hpp"
#include "executor.hpp"

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    ss::parameter para;
    LoadOptions(argc, argv, para);
    mt::mpiPartitioner(para);

}

