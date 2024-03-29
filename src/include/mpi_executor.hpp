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

	class MpiPartition{
	private:
		int _dim;
		int _total_partition;
		vector<int> _map;
		hnswlib::L2Space _l2space;
		hnswlib::HierarchicalNSW<float> _hnsw;

		int load_map(string map_path){
			ifstream fin(map_path);
			fin >> _total_partition;
			int iter, buffer;
			fin >> iter;
			for (int i = 0; i < iter; i++){
				fin >> buffer;
				_map.push_back(buffer);
			}
			return iter;
		}
	public:
		MpiPartition(int dim, string hnsw_path, string map_path):_dim(dim), _l2space(dim),_hnsw(&_l2space, hnsw_path){
			int size = load_map(map_path);
			assert(size == _hnsw.max_elements_);
		}

		int searchHnsw(float* query){
			std::priority_queue<std::pair<float, long unsigned int > > result = _hnsw.searchKnn(query, 1);
			return _map[result.top().second];
		}

		int getTotalPartition(){
			return _total_partition;
		}
	};

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

	void mpiPartitioner(ss::parameter& para){
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
		ss::Matrix<float> data(para.hdfs_host, para.hdfs_port, para.base_data, world_rank, world_size, para.base_size);
		long long load_time = dhnsw::get_current_time_milliseconds();
		cout << "#[timer] load file use " + std::to_string(load_time - start_time) + " milisecond\n";

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



    void mpiBody(ss::parameter& para, mt::Partition& partition){
		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);


		if (world_size != SIZEWORKER + 2){
			cout << "#[error ] wrong number process initialled" << endl;
			MPI_Abort(MPI_COMM_WORLD, 0);
		}

		if (world_rank == world_size - 2){
		    void* v;
		    int flag;
		    MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_WTIME_IS_GLOBAL, &v, &flag);
		    if(flag) {
		    	int vval = *(int*)v;
		    	cout << "MPI_WTIME_IS_GLOBAL is " + std::to_string(vval) << endl;
		    }
		    else {
		    	cout << "MPI_WTIME_IS_GLOBAL NOT SET" << endl;
		    }
			//logic for task sender
			cout << "#[mpi ] sender start" << endl;
			ss::Matrix<float> query(para.query_data);
			mt::Sender* sender;
			vector<vector<float> > centroids;
			loadCentroids(centroids, para.centroids_file);
			if (para.mode_code / 10){
				sender = new Sender(world_size - 2 ,query, centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER, para.sender_ef);
				sender->saveHNSW(para.hnsw_dir + "/hnsw_sender");
			}
			else
				sender = new Sender(world_size - 2, query, para.hnsw_dir + "/hnsw_meta", centroids, partition, DATA_DIMENSION, centroids.size(), SIZEWORKER, para.sender_ef);
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
			int total_wakeup = 0;
			for (int i = 0; i < query.getSize(); i++)
				sendMessage(i, sender, total_wakeup);
			cout << "#[sender ] finish sending all the task with wake rate: " + std::to_string(total_wakeup * 1.0 / (SIZEWORKER * query.getSize() * 1.0)) << endl;
		}
		if (world_rank == world_size - 1){
			//logic for result receiver
			Bencher truth_bench(para.ground_truth.c_str());
			mt::Receiver receiver(QUERY_SIZE);
            MPI_Barrier(MPI_COMM_WORLD); // wait for sender to cluster
            MPI_Barrier(MPI_COMM_WORLD); // wait for slaves to construct HNSW
//            while(true) {
                double avg_time;
				vector<vector<pair<float, int>>> result = receiver.receive(avg_time);
				Bencher current_bench(result, false);
				cout << "time || recall"<< endl << std::to_string(avg_time) + " " + std::to_string(truth_bench.avg_recall(current_bench)) << endl;
//            }

		}
		else{
			//logic for slaves
			MPI_Barrier(MPI_COMM_WORLD);
			mt::Slave* slave;
			if (para.mode_code % 10){
				ss::Matrix<float> data(para.base_data);
				slave = new Slave(data, para.subset_dir + "/slave" + std::to_string(world_rank), para.slave_ef);
				slave->saveHNSW(para.hnsw_dir + "/hnsw_slave" + std::to_string(world_rank));
			}
			else
				slave = new Slave(para.hnsw_dir + "/hnsw_slave" + std::to_string(world_rank), para.subset_dir + "/slave" + std::to_string(world_rank), para.slave_ef);
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



