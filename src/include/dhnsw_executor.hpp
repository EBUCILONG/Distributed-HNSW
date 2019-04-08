#pragma once

#include <vector>
#include <mpi.h>
#include <iostream>
#include <thread>

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

    void worker_func() {
        //TODO: Implement worker logic
    }

    void receiver_func() {
//        Receiver receiver =
    }

    void dhnsw_execute(ss::parameter& para, mt::Partition& partition) {
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
        // get task successful, launch threads
        //TODO: Fill in arguments for thread functions
//        std::thread receiver_thread(receiver_func, args...);
//        std::thread worker_threads[para.num_thread];
//        for(int i=0; i<para.num_thread; i++) worker_threads[i] = std::thread(worker_func);

        //TODO: Implement coordinator logic

    }
}



