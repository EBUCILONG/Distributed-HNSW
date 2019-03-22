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

#include <boost/program_options/options_description.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/errors.hpp>

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

	void sendMessage(int index, Sender* sender){
		task_message tm;
		vector<int> destinations;
		sender->makeTask(index, destinations, tm, MPI_Wtime());
		for (int j = 0; j < destinations.size(); j++)
			MPI_Send((void*) &tm, sizeof(task_message), MPI_BYTE, destinations[j], TASK_TAG, MPI_COMM_WORLD);
	}

	void receiveResultMessage(void* buffer, int msg_len){
		MPI_Recv(buffer, msg_len, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG,
		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

    void mpiBody(ss::parameter& para, mt::Partition& partition){
        MPI_Init(NULL, NULL);
		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		if (world_size != SIZEWORKER + 2){
			cout << "#[error ] wrong process initialled" << endl;
			MPI_Abort(MPI_COMM_WORLD, 0);
		}

		if (world_rank == world_size - 2){
			//logic for task sender
			ss::Matrix<float> query(para.query_data);
			mt::Sender* sender;
			vector<vector<float> > centroids;
			loadCentroids(centroids, para.centroids_file);
			if (para.mode_code / 10){
				sender = new Sender(world_size - 2 ,query, centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER);
				sender->saveHNSW(para.hnsw_dir + "/hnsw_sender");
			}
			else
				sender = new Sender(world_size - 2, query, para.hnsw_dir + "/hnsw_sender", centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER);

			vector<vector<int> > clusters;
			mt::loadClusters(clusters, para.cluster_file);

			for (int i = 0; i < SIZEWORKER; i++){
				vector<int> members = sender->_waker.getMember(i);
				vector<int> subset;
				for (int j = 0; j < members.size(); j++)
					subset.insert(subset.end(), clusters[members[j]].begin(), clusters[members[j]].end());
				saveSubset(i, subset, para.subset_dir);
			}



			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Barrier(MPI_COMM_WORLD);
			for (int i = 0; i < query.getSize(); i++)
				sendMessage(i, sender);
			cout << "#[sender ] finish sending all the task" << endl;
		}
		if (world_rank == world_size - 1){
			//logic for result receiver
			Bencher truth_bench(para.ground_truth.c_str());
			mt::Receiver receiver(para.query_size);
            MPI_Barrier(MPI_COMM_WORLD); // wait for sender to cluster
            MPI_Barrier(MPI_COMM_WORLD); // wait for slaves to construct HNSW
//            while(true) {
				vector<vector<pair<float, int>>> result = receiver.receive();
				Bencher current_bench(result, false);
				cout << truth_bench.avg_recall(current_bench) << endl;
//            }

		}
		else{
			//logic for slaves
			MPI_Barrier(MPI_COMM_WORLD);
			mt::Slave* slave;
			if (para.mode_code % 10){
				ss::Matrix<float> data(para.base_data);
				slave = new Slave(data, para.subset_dir + "/slave" + std::to_string(world_rank), 100);
				slave->saveHNSW(para.hnsw_dir + "hnsw_slave" + std::to_string(world_rank));
			}
			else
				slave = new Slave(para.hnsw_dir + "hnsw_slave" + std::to_string(world_rank), para.subset_dir + "/slave" + std::to_string(world_rank), 100);
			MPI_Barrier(MPI_COMM_WORLD);
			while(true){
				task_message tm;
				MPI_Recv((void*) &tm,sizeof(task_message), MPI_BYTE, world_size - 2, TASK_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				result_message rm;
				slave->makeResult(tm, rm);
				MPI_Send((void*) &rm, sizeof(result_message), MPI_BYTE, world_size - 1, RESULT_TAG, MPI_COMM_WORLD);
			}
		}
		MPI_Finalize();
	}

}



