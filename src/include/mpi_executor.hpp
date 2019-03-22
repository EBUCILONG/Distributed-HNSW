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

using std::cout;
using std::endl;
using std::vector;
using std::string;

#define SIZEWORKER 10

/*
 * status code with two digit:
 * first for sender: 0 load hnsw 1 retrain hnsw and save
 * second for slave: 0 load hnsw 1 retrain hnsw and save
 */

namespace mt {

	void sendMessage(int index, Sender& sender){
		task_message tm;
		vector<int> destinations;
		sender.makeTask(index, destinations, tm, MPI_Wtime());
		for (int j = 0; j < destinations.size(); j++)
			MPI_Send((void*) tm, sizeof(task_message), MPI_BYTE, destinations[j], TASK_TAG, MPI_COMM_WORLD);
	}


	template<class Partition>
	void mpiBody(ss::parameter& para){

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
			mt::Sender sender;
			vector<vector<float> > centroids;
			loadCentroids(centroids, para.centroids_file);
			Partition partition;
			if (para.mode_code / 10){
				sender(world_size - 2 ,query, centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER);
				sender.saveHNSW(para.hnsw_dir + "/hnsw_sender");
			}
			else
				sender(world_size - 2, query, para.hnsw_dir + "/hnsw_sender", centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER);

			vector<vector<int> > clusters;
			mt::loadClusters(clusters, para.cluster_file);

			for (int i = 0; i < SIZEWORKER; i++){
				vector<int> members = sender._waker.getMember(i);
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

		}
		else{
			//logic for slaves
			MPI_Barrier(MPI_COMM_WORLD);
			mt::Slave slave;
			if (para.mode_code % 10){
				ss::Matrix<float> data(para.base_data);
				slave(data, para.subset_dir + "/slave" + std::to_string(world_rank), 100);
				slave.saveHNSW(para.hnsw_dir + "hnsw_slave" + std::to_string(world_rank));
			}
			else
				slave(para.hnsw_dir + "hnsw_slave" + std::to_string(world_rank), para.subset_dir + "/slave" + std::to_string(world_rank), 100);
			MPI_Barrier(MPI_COMM_WORLD);
			while(true){
				task_message tm;
				MPI_Recv(
				    void* data,
				    int count,
				    MPI_Datatype datatype,
				    int source,
				    int tag,
				    MPI_Comm communicator,
				    MPI_Status* status)
			}
		}
	}

}



