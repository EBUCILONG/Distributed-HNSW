/*
 * fvecs_hnsw_machine.cpp
 *
 *  Created on: 30 Apr 2019
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
    ss::Matrix<float> data(para.base_data);
    dhnsw::fvecs_hnsw_machine(data, para.out_dir + "/hnsw/partition");
}


