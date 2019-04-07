//
// Created by Michael Jiang on 2019-04-07.
//

#pragma once

#include <iostream>
#include <string>
#include <zookeeper/zookeeper.h>

#define MAX_PATH_LEN 128

using std::string;
using std::cout;
using std::endl;

namespace dhnsw {
    enum lock_status {
        LOCK_SUCCESS, LOCK_OCCUPIED, LOCK_FAILURE
    };
    class TaskControl {
        const char* _hosts;
        const int _timeout;
        const int _n_tasks;
        const int _n_duplicate;
        zhandle_t* _handle;

        int _lock_acquire(zhandle_t *zh, const char *path) {
            char path_buffer[MAX_PATH_LEN];
            int buffer_len=sizeof(path_buffer);
            int flag = zoo_create(zh, path,"lock",4, &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, path_buffer, buffer_len);
            int ret = -1;
            if (flag == ZOK) {
                ret = 0;
            } else if (flag == ZNODEEXISTS) ret = 1;
            else ret = 2; // ERROR
            return ret;
        }

        static void _connection_watcher(zhandle_t* zh, int type, int state, const char* path, void* watcherCtx) {
//            if (type == ZOO_SESSION_EVENT) {
//                if (state == ZOO_CONNECTED_STATE) cout << "[ZK] Connected to ZooKeeper server." << endl;
//                else if (state == ZOO_EXPIRED_SESSION_STATE) cout << "[ZK] Session expired." << endl;
//            }
        }

    public:
        TaskControl(const char* hosts, int n_tasks, int n_duplicate, int timeout = 30000): _hosts(hosts), _timeout(timeout),
        _n_tasks(n_tasks), _n_duplicate(n_duplicate) {
            _handle = zookeeper_init(_hosts, _connection_watcher,  _timeout, NULL, (void*)"init", 0);
            assert(_handle != NULL && "[ZK] Failed to connect to ZooKeeper server.");
        }

        /**
         * \brief Get a task from ZK servers.
         *
         * \param task_path path to the lock directory (without '/' at the end)
         * \param task_number contains the id of the task (if successful)
         * \return 0 if get successful, otherwise failed
         */
        int getTask(const char* task_path, int& task_number, int& process_id) {
            string lock_dir(task_path);
            // see if any of the tasks is empty
            for(int i=0; i<_n_tasks; i++) {
                // construct task folder name
                for(int j=0; j<_n_duplicate; j++) {
                    string task_node(lock_dir);
                    task_node += "/" + std::to_string(i) + "/lock" + std::to_string(j);
                    int re = _lock_acquire(_handle, task_node.c_str());
                    if(re == 0) {
                        // successfully acquired
                        task_number = i;
                        process_id = i*_n_duplicate + j;
                        return LOCK_SUCCESS;
                    }
                    else if(re == 1) continue;
                    else return LOCK_FAILURE;
                }
            }
            return LOCK_OCCUPIED;
        }
    };
}



