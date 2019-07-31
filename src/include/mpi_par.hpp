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



    void smart_partitioner(ss::parameter& para){
        /*
         * using para
         * base_data out_dir containing /hnsw/partition /partition_map
         */
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

//		if (world_size != SIZEWORKER){
//			cout << "#[error ] wrong number process initialled with" + std::to_string(world_size) << endl;
//			MPI_Abort(MPI_COMM_WORLD, 0);
//		}


        long long start_time = dhnsw::get_current_time_milliseconds();
        ss::Matrix<float> data(para.base_data, para.dim);
//        ss::Matrix<float> data(para.hdfs_host, para.hdfs_port, para.base_data, world_rank, world_size, para.base_size);
        long long load_time = dhnsw::get_current_time_milliseconds();


        MpiPartition partitioner(data.getDim(), para.out_dir + "/hnsw/partition", para.out_dir + "/partition_map");
        long long construct_time = dhnsw::get_current_time_milliseconds();
        cout << "#[timer] construct partitioner use " + std::to_string(construct_time - load_time) + " milisecond\n";

        omp_set_num_threads(20);
        int sizer = data.getSize();
        vector<int> result(sizer);
        cout << "start partition\n";
#pragma omp parallel for
        for (int i = 0; i < sizer; i++){
            result[i] = partitioner.searchHnsw(data[i]);
        }

        long long partition_time = dhnsw::get_current_time_milliseconds();
        cout << "#[timer] partition use " + std::to_string(partition_time - construct_time) + " milisecond\n";
        cout << "#[worker]"+std::to_string(world_rank) + " start to save\n";

        vector<std::ofstream* > fouts;
        for (int i = 0; i < partitioner.getTotalPartition(); i++){
            std::ofstream* fout = new std::ofstream(para.out_dir + "/subfile/w" + std::to_string(world_rank) + "/partition" + std::to_string(i), std::iostream::binary);
            fouts.push_back(fout);
        }
        int dimer = data.getDim();
        for (int i = 0; i < sizer; i++){
            std::ofstream* fout = fouts[result[i]];
            fout->write((char*)&dimer, sizeof(int));
            fout->write((char*)data[i], dimer * sizeof(float));
            fout->write((char*)&data.id_[i], sizeof(int));
        }
        for(int i = 0; i < partitioner.getTotalPartition(); i++){
            fouts[i]->close();
            delete fouts[i];
        }
        long long save_time = dhnsw::get_current_time_milliseconds();
        cout << "#[timer] save use " + std::to_string(save_time - partition_time) + " milisecond\n";
    }


}



