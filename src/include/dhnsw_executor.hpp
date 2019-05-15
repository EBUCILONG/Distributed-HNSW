#pragma once

#include <vector>
#include <mpi.h>
#include <iostream>
#include <thread>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/errors.hpp>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>

#include "bench/bencher.hpp"
#include "bench/prober.hpp"
#include "parameters.hpp"
#include "matrix.hpp"
#include "metric.hpp"
#include "utils/util.hpp"
#include "utils/cluster.hpp"
#include "hnswlib/hnswlib.h"
#include "hnswlib/hnswalg.h"
#include "hnswlib/space_l2.h"
#include "waker/waker.hpp"
#include "dhnswlib/coordinator.hpp"
#include "dhnswlib/worker.hpp"
#include "dhnswlib/receiver.hpp"
#include "dhnswlib/task_control.hpp"
#include "distributed/macro.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::thread;

namespace dhnsw {

    void coordinator_func(dhnsw::Coordinator* coordinator) {
//        dhnsw::Coordinator coordinator(process_id, hnsw_id, vec_dim, num_centroid, num_subhnsw, wakeup_controller,
//                                       subhnsw, metahnsw, map_dir, producer_config, consumer_config,
//                                       meta_ef, sub_ef);
        coordinator->startWork();
    }

    void worker_func(dhnsw::Worker* worker){
        worker->startWork();
    }

    void receiver_func(dhnsw::Receiver* receiver) {
        receiver->receive();
    }

    void dhnsw_execute(ss::parameter& para) {
        // get task from ZooKeeper
        int sub_hnsw_id = -1, process_id = -1;
        TaskControl tc(para.hosts);
        int status = tc.getTask(sub_hnsw_id, process_id);
        if(status == LOCK_FAILURE) {
            cout << "[EXEC] Failed to get task due to TaskControl Error." << endl;
            exit(-1);
        } else if(status == LOCK_OCCUPIED) {
            cout << "[EXEC] All tasks occupied." << endl;
            return;
        }
        cout << "[EXECUTE] PROCESS ID: "<< process_id << " SUB_HNSW_ID: "<< sub_hnsw_id << endl;
        // get task successful
        string worker_group = "subhnsw_g_";
        worker_group += std::to_string(sub_hnsw_id);
        string coordinator_group = "query_g";
        string receiver_group = "receiver_g_";
        receiver_group += std::to_string(process_id);

        cout << "[ALL] :" << para.broker_list << endl;

        cppkafka::Configuration coordinator_consumer_config = {
                { "metadata.broker.list", para.broker_list},
                { "group.id",  coordinator_group},
                { "enable.auto.commit", true},
                {"enable.auto.offset.store", false},
                {"fetch.wait.max.ms", 1000},
//                {"debug", "msg"}
        };

        cppkafka::Configuration worker_consumer_config = {
                { "metadata.broker.list", para.broker_list},
                { "group.id",  worker_group},
                { "enable.auto.commit", true },
                {"fetch.wait.max.ms", 1000},
                {"enable.auto.offset.store", false},
//                {"debug", "msg"}
        };

        cppkafka::Configuration receiver_consumer_config = {
                { "metadata.broker.list", para.broker_list},
                { "group.id",  receiver_group},
                { "enable.auto.commit", true },
                {"enable.auto.offset.store", false},
                {"fetch.wait.max.ms", 1000},
//                {"debug", "msg"}
        };

        cppkafka::Configuration producer_config = {
                { "metadata.broker.list", para.broker_list},
//                { "queue.buffering.max.ms", 100},
//                {"debug", "msg"}
        };

        dhnsw::Coordinator coordinator( process_id, sub_hnsw_id, para.dim, para.num_centroid,
                                        para.num_subhnsw, para.wake_up_controller, para.hnsw_dir + "/hnsw_slave" + std::to_string(sub_hnsw_id),
                                        para.hnsw_dir + "/hnsw_meta", para.map_address, producer_config, coordinator_consumer_config,
                                        para.sender_ef, para.slave_ef);

        dhnsw::Worker worker(sub_hnsw_id, para.topK, para.dim, coordinator._subhnsw_addr, worker_consumer_config, producer_config);

        Receiver receiver(process_id, para.topK, receiver_consumer_config, producer_config);

        std::thread coordinator_threads[para.num_coordinator];
        for(int i=0; i<para.num_coordinator; i++)
            coordinator_threads[i] = std::thread(coordinator_func, &coordinator);

        std::thread worker_threads[para.num_worker];
        for(int i = 0; i < para.num_worker; i++)
            worker_threads[i] = std::thread(worker_func, &worker);

//        std::thread receiver_thread(receiver_func, &receiver);
        receiver.receive();
    }
}



