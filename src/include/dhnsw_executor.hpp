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

    void worker_func(int subhnsw_id, int top_k, int data_dim, hnswlib::HierarchicalNSW<float>* hnsw, cppkafka::Configuration consumer_config, cppkafka::Configuration producer_config) {
        dhnsw::Worker worker(subhnsw_id, top_k, data_dim, hnsw, consumer_config, producer_config);
        worker.startWork();
    }

    void receiver_func(int process_id, const cppkafka::Configuration& consumer_config,
                       const cppkafka::Configuration& producer_config) {
        Receiver receiver(process_id, consumer_config, producer_config);
        receiver.receive();
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
        //TODO: Implement coordinator logic
        string worker_group = "subhnsw_g_";
        worker_group += std::to_string(sub_hnsw_id);
        string coordinator_group = "query_g";
        string receiver_group = "receiver_g_";
        receiver_group += std::to_string(process_id);

        cppkafka::Configuration coordinator_consumer_config = {
                { "metadata.broker.list", para.broker_list},
                { "group.id",  coordinator_group},
                { "enable.auto.commit", false}
        };

        cppkafka::Configuration worker_consumer_config = {
                { "metadata.broker.list", para.broker_list},
                { "group.id",  worker_group},
                { "enable.auto.commit", false }
        };

        cppkafka::Configuration receiver_consumer_config = {
                { "metadata.broker.list", para.broker_list},
                { "group.id",  receiver_group},
                { "enable.auto.commit", false }
        };

        cppkafka::Configuration producer_config = {
                { "metadata.broker.list", para.broker_list}
        };
        dhnsw::Coordinator coordinator(process_id, sub_hnsw_id, para.dim, para.num_centroid, para.num_subhnsw, para.wake_up_controller, para.hnsw_dir + "/hnsw_slave" + std::to_string(sub_hnsw_id), para.hnsw_dir + "/hnsw_meta", para.map_address, producer_config, coordinator_consumer_config, para.sender_ef, para.slave_ef);

        std::thread worker_threads[para.num_worker];
        for(int i = 0; i < para.num_worker; i++)
            worker_threads[i] = std::thread(worker_func, sub_hnsw_id, para.topK, para.dim, coordinator._subhnsw_addr, worker_consumer_config, producer_config);

        std::thread receiver(receiver_func, process_id, receiver_consumer_config, producer_config);

        coordinator.startWork();
    }
}



