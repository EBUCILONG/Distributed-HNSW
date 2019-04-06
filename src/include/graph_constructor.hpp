/*
 * mpi_executor.hpp
 *
 *  Created on: 22 Mar 2019
 *      Author: oruqimaru
 */

#pragma once

#include <vector>
#include <omp.h>
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

	void sendMessage(int index, Sender* sender, int& counter){
		task_message tm;
		vector<int> destinations;
		sender->makeTask(index, destinations, tm, MPI_Wtime());
		counter += tm.num_wake_up;
		for (int j = 0; j < destinations.size(); j++)
			MPI_Send((void*) &tm, sizeof(task_message), MPI_BYTE, destinations[j], TASK_TAG, MPI_COMM_WORLD);
	}

	void receiveResultMessage(void* buffer, int msg_len){
		MPI_Recv(buffer, msg_len, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG,
		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

    void mpiBody(ss::parameter& para, mt::Partition& partition){
		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);


		if (world_size != SIZEWORKER + 1){
			cout << "#[error ] wrong number process initialled" << endl;
			MPI_Abort(MPI_COMM_WORLD, 0);
		}

		if (world_rank == world_size - 1){
			//logic for task sender
			cout << "#[mpi ] sender start" << endl;
			mt::Sender* sender;
			ss::Matrix<float> query;
			vector<vector<float> > centroids;
			loadCentroids(centroids, para.centroids_file);
			sender = new Sender(world_size - 1,query, centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER, para.sender_ef);
			sender->saveHNSW(para.hnsw_dir + "/hnsw_sender");
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
		}
		else{
			//logic for slaves
			MPI_Barrier(MPI_COMM_WORLD);
			mt::Slave* slave;
			ss::Matrix<float> data(para.base_data);
			slave = new Slave(data, para.subset_dir + "/slave" + std::to_string(world_rank), para.slave_ef);
			slave->saveHNSW(para.hnsw_dir + "/hnsw_slave" + std::to_string(world_rank));
		}
		MPI_Finalize();
	}

}



