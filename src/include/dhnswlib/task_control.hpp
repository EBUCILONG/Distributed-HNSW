//
// Created by Michael Jiang on 2019-04-07.
//

#pragma once

#include <iostream>
#include <string>
#include <zookeeper/zookeeper.h>

#define MAX_PATH_LEN 128
#define MAX_TASK_NUMBER 128
#define VALUE_BUFFER_LEN 20

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

        bool _get_n_tasks(const string& lock_dir, int& n_tasks) {
            struct String_vector children = {-1, (char**)malloc(sizeof(char*)*MAX_TASK_NUMBER)};
            int ret = zoo_get_children(_handle, lock_dir.c_str(), 0, &children);
            if(ret == ZOK && children.count != 0) {
                // get children successful
                n_tasks = children.count;
                return true;
            }
            return false;
        }

        bool _get_n_duplicate(const string& lock_dir, int& n_duplicate) {
            char str[VALUE_BUFFER_LEN];
            int buffer_len = VALUE_BUFFER_LEN;
            int ret = zoo_get(_handle, lock_dir.c_str(), 0, str, &buffer_len, NULL);
            if(ret == ZOK) {
                n_duplicate = std::atoi(str);
                return true;
            }
            return false;
        }

    public:
        explicit TaskControl(const string& hosts, int timeout = 30000): _hosts(hosts.c_str()),
        _timeout(timeout) {
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
        int getTask(int& task_number, int& process_id, const string& lock_dir = "/dhnsw") {
            // get number of tasks
            int n_tasks = 0, n_duplicate = 0;
            if(!(_get_n_tasks(lock_dir, n_tasks) && _get_n_duplicate(lock_dir, n_duplicate))) //check if failed
                return LOCK_FAILURE;
            // see if any of the tasks is empty
            for(int i=0; i<n_tasks; i++) {
                // construct task folder name
                for(int j=0; j<n_duplicate; j++) {
                    string task_node(lock_dir);
                    task_node += "/" + std::to_string(i) + "/lock" + std::to_string(j);
                    int re = _lock_acquire(_handle, task_node.c_str());
                    if(re == 0) {
                        // successfully acquired
                        task_number = i;
                        process_id = i*n_duplicate + j;
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



