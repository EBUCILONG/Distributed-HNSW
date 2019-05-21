//
// Created by Oruqimaru on 21/5/2019.
//

//
// Created by Oruqimaru on 16/4/2019.
//


#include <vector>
#include <string>

#include "parameters.hpp"
#include "distributed/partition.hpp"
#include "executor.hpp"
#include "dhnswlib/ip_utils.hpp"

using std::vector;
using std::string;

int main(int argc, char** argv){
    mt::Partition partition(1);
    ss::parameter para;
    LoadOptions(argc, argv, para);
    dhnsw::ip_partition(para.num_subhnsw, 3, para.out_dir + "/ball",para.out_dir + "/truth", para.out_dir + "reverse_truth", para.base_data, para.out_dir, partition);
}
