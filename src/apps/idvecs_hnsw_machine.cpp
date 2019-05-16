/*
 * idvecs_hnsw_machine.cpp
 *
 *  Created on: 2 May 2019
 *      Author: oruqimaru
 */

#include <vector>
#include <string>

#include "parameters.hpp"
#include "distributed/partition.hpp"
#include "trainer/trainer.hpp"
#include "executor.hpp"
#include "matrix.hpp"

using std::vector;
using std::string;

int main(int argc, char** argv){
    ss::parameter para;
    LoadOptions(argc, argv, para);
    omp_set_num_threads(24);
    dhnsw::idvecs_hnsw_machine(para.base_data, para.out_dir + "/hnsw/partition", 10);
}



