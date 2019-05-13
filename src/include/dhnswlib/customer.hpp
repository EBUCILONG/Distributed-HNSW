//
// Created by Oruqimaru on 10/4/2019.
//

#pragma once

#include <ctime>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <set>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <cppkafka/message_builder.h>
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <cppkafka/consumer.h>
#include <cppkafka/producer.h>

#include "dhnswlib/time.hpp"
#include "waker/waker.hpp"
#include "hnswlib/hnswalg.h"
#include "utils/binstream.hpp"
#include "matrix.hpp"

using husky::base::BinStream;
using std::stringstream;
using std::pair;
using std::priority_queue;
using std::set;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

namespace dhnsw {
    class QueryMessage{
    public:
        int query_id_;
        vector<float> query_;
        long long start_time_;

        QueryMessage(int query_id, float* query_addr, int vec_dim):
        query_id_(query_id){
            for(int i = 0; i < vec_dim; i++)
                query_.push_back(query_addr[i]);
//            cout << query_id << " ";
//            for(int i = 0; i < vec_dim; i++)
//                cout << query_[i] << " ";
//            cout << endl;
            start_time_ = get_current_time_milliseconds();
        }

        QueryMessage(int vec_dim, string input_string){
            vector<char> buffer(input_string.length());
            std::copy(input_string.c_str(), input_string.c_str() + input_string.length(), buffer.begin());
            BinStream bs(buffer);
            int sizer;
            bs >> query_id_ >> sizer;
            if (sizer != vec_dim){
                cout << "#[error ] wrong vector size" << endl;
                assert(0);
            }
            float float_buffer;
            for (int i = 0; i < sizer; i++){
                bs >> float_buffer;
                query_.push_back(float_buffer);
            }
            bs >> start_time_;
        }

        string toString(){
            BinStream bs;
            bs << query_id_ << int(query_.size());
            for (int i =0 ; i < query_.size(); i++)
                bs << query_[i];
            bs << start_time_;
            return bs.to_string();
        }
    };

    class Customer{
    private:
        ss::Matrix<float>& _querys;
        int _num_subhnsw;
        cppkafka::Producer _producer;
        int _messages_sent;
        std::chrono::milliseconds _timeout;

    public:
        Customer(int num_subhnsw, ss::Matrix<float>& querys, cppkafka::Configuration config):
        _querys(querys),
        _num_subhnsw(num_subhnsw),
        _producer(config),
        _messages_sent(0),
        _timeout(30000) {
        }

        void send_message(unsigned interval){
            int sizer = _querys.getSize();
            int dimer = _querys.getDim();
            string topic("query_t");
            for (int i = 0; i < sizer; i++) {
                QueryMessage qm(i, _querys[i], dimer);
                string payload = qm.toString();
                _producer.produce(cppkafka::MessageBuilder(topic.c_str()).payload(payload));
                if(interval != 0) usleep(interval);
                _messages_sent ++;
//                cout << "[CUST] Produced " << _messages_sent << " messages." << endl;
            }
        }

        void idle(){
            while(true){
                cout << "idling" << endl;
                sleep(2);
            }
        }
    };
}