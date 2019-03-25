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
//		cout << "#[sender] Sent a message." << endl;
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

//		cout << "#[mpi ] process " + std::to_string(world_rank) + " finish mpi initiallizing\n";

		if (world_size != SIZEWORKER + 2){
			cout << "#[error ] wrong number process initialled" << endl;
			MPI_Abort(MPI_COMM_WORLD, 0);
		}

		if (world_rank == world_size - 2){
			//logic for task sender
			cout << "#[mpi ] sender start" << endl;
			ss::Matrix<float> query(para.query_data);
			mt::Sender* sender;
			vector<vector<float> > centroids;
			loadCentroids(centroids, para.centroids_file);
//			cout << "#[sender] Sender loaded centroids." << endl;
			if (para.mode_code / 10){
				sender = new Sender(world_size - 2 ,query, centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER);
				sender->saveHNSW(para.hnsw_dir + "/hnsw_sender");
			}
			else
				sender = new Sender(world_size - 2, query, para.hnsw_dir + "/hnsw_sender", centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER);
//            cout << "#[sender ] Finished initializing Sender object." << endl;
			vector<vector<int> > clusters;
			mt::loadClusters(clusters, para.cluster_file);
//            cout << "#[sender ] Finished loading clusters." << endl;
			for (int i = 0; i < SIZEWORKER; i++){
				vector<int> members = sender->_waker.getMember(i);
				vector<int> subset;
				for (int j = 0; j < members.size(); j++)
					subset.insert(subset.end(), clusters[members[j]].begin(), clusters[members[j]].end());
				saveSubset(i, subset, para.subset_dir);
			}


//			cout << "#[mpi ] sender finish partition and hit first barrier" << endl;
			MPI_Barrier(MPI_COMM_WORLD);
//			cout << "#[mpi ] sender hit second barrier and wait for slave to finish learning" << endl;
			MPI_Barrier(MPI_COMM_WORLD);
			for (int i = 0; i < query.getSize(); i++)
				sendMessage(i, sender);
			cout << "#[sender ] finish sending all the task with wake rate " + std::to_string(sender->_waker.getAverWake()) << endl;
		}
		if (world_rank == world_size - 1){
			//logic for result receiver
//			cout << "#[mpi ] receiver start \n";
			Bencher truth_bench(para.ground_truth.c_str());
			mt::Receiver receiver(QUERY_SIZE);
//            cout << "#[mpi ] Before receiver barrier 1." << endl;
            MPI_Barrier(MPI_COMM_WORLD); // wait for sender to cluster
//			cout << "#[mpi ] Before receiver barrier 2." << endl;
            MPI_Barrier(MPI_COMM_WORLD); // wait for slaves to construct HNSW
//            while(true) {
            	cout << "#[mpi ] After receiver barrier 2." << endl;
				vector<vector<pair<float, int>>> result = receiver.receive();
				Bencher current_bench(result, false);
//				cout << "#[bench] bench size: " << std::to_string(current_bench.size()) << endl;
				cout << truth_bench.avg_recall(current_bench) << endl;
//            }
//            cout << "#[mpi ] Receiver Finished." << endl;

		}
		else{
			//logic for slaves
//			cout << "#[slav] " + std::to_string(world_rank) + " before barrier 1." << endl;
			MPI_Barrier(MPI_COMM_WORLD);
//			cout << "#[slav] First Barrier Breached!" << endl;
			mt::Slave* slave;
			if (para.mode_code % 10){
				ss::Matrix<float> data(para.base_data);
//                cout << "#[slav] Before constructing slave." << endl;
				slave = new Slave(data, para.subset_dir + "/slave" + std::to_string(world_rank), 100);
				slave->saveHNSW(para.hnsw_dir + "/hnsw_slave" + std::to_string(world_rank));
//                cout << "#[slav] After saving hnsw." << endl;
			}
			else
				slave = new Slave(para.hnsw_dir + "/hnsw_slave" + std::to_string(world_rank), para.subset_dir + "/slave" + std::to_string(world_rank), 100);
			MPI_Barrier(MPI_COMM_WORLD);
//			cout << "#[slav] Second Barrier Breached." << endl;
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



