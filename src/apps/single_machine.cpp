//
// Created by Oruqimaru on 16/4/2019.
//

#include <vector>
#include <string>

#include "parameters.hpp"
#include "distributed/partition.hpp"
#include "trainer/trainer.hpp"
#include "executor.hpp"

using std::vector;
using std::string;

int main(int argc, char** argv){
	mt::Partition partition(1);
	ss::parameter para;
	LoadOptions(argc, argv, para);
	dhnsw::single_machine_trainer(para.dim, para.num_centroid, para.num_subhnsw, para.base_data, para.out_dir + "/centroids", para.out_dir + "/map", para.out_dir + "/partition_map", para.out_dir + "/hnsw/meta", partition, 32, 100);
}
