/*
 * wakerate_tester.cpp
 *
 *  Created on: 1 May 2019
 *      Author: oruqimaru
 */


#include <vector>
#include <string>

#include "parameters.hpp"
#include "distributed/partition.hpp"
#include "trainer/trainer.hpp"
#include "executor.hpp"
#include "matrix.hpp"
#include "evaluator/evaluate_tools.hpp"

using std::vector;
using std::string;

int main(int argc, char** argv){
	ss::parameter para;
	LoadOptions(argc, argv, para);
	ss::Matrix<float> data(para.base_data);
	eva::test_wake_rate(para.out_dir + "/hnsw/meta", para.out_dir + "/map", para.query_data);
}


