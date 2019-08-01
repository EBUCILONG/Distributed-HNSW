//
// Created by Oruqimaru on 30/7/2019.
//

/*
 * mpi_executor.hpp
 *
 *  Created on: 22 Mar 2019
 *      Author: oruqimaru
 */

#pragma once

#include <vector>
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <queue>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/errors.hpp>

#include "dhnswlib/time.hpp"
#include "bench/bencher.hpp"
#include "bench/prober.hpp"
#include "parameters.hpp"
#include "matrix.hpp"
#include "metric.hpp"
#include "utils/util.hpp"
#include "utils/cluster.hpp"
#include "hnswlib/hnswlib.h"
#include "hnswlib/space_l2.h"
#include "waker/waker.hpp"
#include "distributed/sender.hpp"
#include "distributed/slave.hpp"
#include "distributed/receiver.hpp"
#include "distributed/macro.h"
#include "mpi_executor.hpp"

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;

/*
 * status code with two digit:
 * first for sender: 0 load hnsw 1 retrain hnsw and save
 * second for slave: 0 load hnsw 1 retrain hnsw and save
 */

namespace mt {

    int find_max(vector<int>& aimer){
        int result = aimer[0];
        for(int i = 0; i < aimer.size(); i++){
            if (aimer[i] > result)
                result = aimer[i];
        }
        return result;
    }

    int check_only_nonzero(vector<int>& aimer){
        int sum = 0;
        int result;
        for(int i = 0; i < aimer.size(); i++){
            if (aimer[i] != 0){
                sum++;
                result = i;
            }
        }
        if (sum == 1)
            return result;
        else
            return -1;
    }

    void smart_partitioner(ss::parameter& para){
        /*
         * using para
         * base_data out_dir containing /hnsw/partition /partition_map
         */
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        MPI_Aint dimen_p, floatarr_p, id_p;
        int dimen;
        float floatarr[para.dim];
        int id;

        // 获取各个元素之间的相对地址
        MPI_Get_address(&dimen, &dimen_p);
        MPI_Get_address(floatarr, &floatarr_p);
        MPI_Get_address(&id, &id_p);  // 注意注意使用指针

        MPI_Aint displacement[3] = {
                0, // 第一个偏移值为0
                floatarr_p - dimen_p,
                id_p - dimen_p
        };

        MPI_Datatype types[3] = { MPI_INT, MPI_FLOAT, MPI_CHAR };
        int blockLength[3] = { 1, para.dim, 1 };
        MPI_Datatype itemType;
        MPI_Type_create_struct(
                3,
                blockLength, // 分块长度
                displacement, // 偏移值
                types, // 类型
                &itemType // 类型指针
        );
        MPI_Type_commit(&itemType);


//		if (world_size != SIZEWORKER){
//			cout << "#[error ] wrong number process initialled with" + std::to_string(world_size) << endl;
//			MPI_Abort(MPI_COMM_WORLD, 0);
//		}

//////////////////////////////////////////////////////prepare mpi utils finished/////////////////////////////////////////////////

        char* sendBuf=NULL;
        char* recvBuf=NULL;
        std::ofstream fout = std::ofstream(para.out_dir + "/partition" + std::to_string(world_rank), std::iostream::binary);
        vector<vector<int>> map(para.num_subhnsw);
        vector<int> sendCounts(para.num_subhnsw, 0);
        vector<int> recvCounts(para.num_subhnsw, 0);
        {
            long long start_time = dhnsw::get_current_time_milliseconds();
            ss::Matrix<float> data(para.base_data, para.dim);
            long long load_time = dhnsw::get_current_time_milliseconds();
            cout << "#[timer] load file use " + std::to_string(load_time - start_time) + " milisecond\n";
            vector<int> result(data.getSize());
            {
                MpiPartition partitioner(data.getDim(), para.out_dir + "/partition",
                                         para.out_dir + "/partition_map");
                long long construct_time = dhnsw::get_current_time_milliseconds();
                cout << "#[timer] construct partitioner use " + std::to_string(construct_time - load_time) +
                        " milisecond\n";

                omp_set_num_threads(20);
                int sizer = data.getSize();
                cout << "start partition\n";
#pragma omp parallel for
                for (int i = 0; i < sizer; i++) {
                    result[i] = partitioner.searchHnsw(data[i]);
                }

                long long partition_time = dhnsw::get_current_time_milliseconds();
                cout << "#[timer] partition use " + std::to_string(partition_time - construct_time) + " milisecond\n";
            }//free partition

            for (int i = 0; i < result.size(); i++){
                map[result[i]].push_back(i);
                sendCounts[result[i]]++;
            }

            int sizeOfItem = sizeof(float) * para.dim + sizeof(int) * 2;
            MPI_Alltoall(sendCounts.data(), 1, MPI_INT,
                         recvCounts.data(), 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Barrier(MPI_COMM_WORLD);

            sendBuf = (char *) malloc((long long)sizeOfItem * (long long) find_max(sendCounts));
            recvBuf = (char *) malloc((long long)sizeOfItem * (long long) find_max(recvCounts));
            char* cpy_ptr = sendBuf;
            for(int diff = 0; diff < world_size; diff++){
                int aim_partition = (world_rank + diff) % world_size;
                for(int i = 0; i < map[aim_partition].size(); i++){
                    vector<int>& id_que = map[aim_partition];
                    *cpy_ptr = para.dim;
                    cpy_ptr += sizeof(int);
                    memcpy(cpy_ptr, data[id_que[i]], sizeof(float)*para.dim);
                    cpy_ptr += sizeof(float)*para.dim;
                    *cpy_ptr = id_que[i];
                }
                vector<int> sendDiff(world_rank, 0);
                vector<int> recvDiff(world_rank, 0);
                vector<int> zeroSendCount(world_rank, 0);
                vector<int> zeroRecvCount(world_rank, 0);
                zeroSendCount[aim_partition] = sendCounts[aim_partition];
                for (int i = 0; i < zeroSendCount.size(); i++){
                    cout << zeroSendCount[i] << " ";
                }
                MPI_Barrier(MPI_COMM_WORLD);
                MPI_Alltoallv(sendBuf, zeroSendCount.data(), sendDiff.data(), itemType,
                        recvBuf, zeroRecvCount.data(), recvDiff.data(), itemType, MPI_COMM_WORLD);

                int index = check_only_nonzero(zeroRecvCount);
                if(index != (world_size - diff)%world_rank || zeroRecvCount[index] != recvCounts[index])
                    MPI_Abort(MPI_COMM_WORLD, 0);
                fout.write(recvBuf, sizeOfItem*zeroRecvCount[index]);
                MPI_Barrier(MPI_COMM_WORLD);
            }
        }
    }


}



