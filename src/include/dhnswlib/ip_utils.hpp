//
// Created by Oruqimaru on 20/5/2019.
//

#pragma once

#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <set>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <sys/timeb.h>
#include <sys/types.h>

#include "hnswlib/hnswalg.h"
#include "dhnswlib/customer.hpp"
#include "dhnswlib/time.hpp"
#include "waker/waker.hpp"
#include "utils/calculator.hpp"
#include "matrix.hpp"
#include "distributed/partition.hpp"

using std::vector;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

namespace dhnsw{

    void load_ball(vector<vector<float> >& ball, string path){
        ifstream fin (path);
        int sizer, dim;
        float buffer;
        ball.resize(sizer);
        for (int i = 0; i < sizer; i++){
            for (int j = 0; j < dim; j++){
                fin >> buffer;
                ball[i].push_back(buffer);
            }
        }
    }

    int ip_partition(int num_subhnsw, int num_replica, string ball_path,string truth_path, string reverse_truth_path, string base_file, string out_dir, mt::Partition& partition,int hnsw_m = 32, int hnsw_ef = 100){
        omp_set_num_threads(24);
        ss::Matrix<float> ball(ball_path);
        vector<vector<float> > vec_ball(ball.getSize());
        for (int i = 0; i < ball.getSize(); i++){
            for (int j = 0; j < ball.getDim(); j++)
                vec_ball[i].push_back(ball[i][j]);
        }
        ss::Matrix<int> groud_truth(truth_path);
        ss::Matrix<int> reverse_truth(reverse_truth_path);
        vector<vector<int> > sub_space(ball.getSize());
        vector<int> sub_size(ball.getSize());
        std::set<int> set;
        for (int i = 0; i < groud_truth.getSize(); i++)
            set.insert(i);

        for (int i = 0; i < groud_truth.getSize(); i++){
            for (int j = 0; j < num_replica; j++){
                sub_space[i].push_back(groud_truth[i][j]);
                set.erase(groud_truth[i][j]);
            }
        }

        std::set<int>::iterator it;
        for (it=set.begin(); it != set.end(); it++){
            sub_space[*reverse_truth[*it]].push_back(*it);
        }

        hnswlib::L2Space l2space(ball.getDim());
        hnswlib::HierarchicalNSW<float> meta(&l2space, ball.getSize(), hnsw_m, hnsw_ef);

        for (int i = 0; i < 1; i++) {
            meta.addPoint((void *) ball[i], (size_t) i);
        }
#pragma omp parallel for
        for (int i = 1; i < ball.getSize(); i++) {
            meta.addPoint((void *) ball[i], (size_t) i);
        }

        cout << "finish constructing hnsw" << endl;

        vector<vector<int> > graph;
        int num_edges = meta.getLevel0Graph(graph);
        for (int i = 0; i < ball.getSize(); i++){
            sub_size[i] = sub_space[i].size();
        }
        vector<int> map = partition.getPartition(graph, vec_ball, sub_size, num_edges, num_subhnsw);
        vector<int> space_size(num_subhnsw, 0);
        vector<vector<int> > partition_result(num_subhnsw);

        cout << "finish partition" << endl;

        for (int i = 0; i < map.size(); i++){
            partition_result[map[i]].push_back(i);
            space_size[map[i]]++;
        }
        cout << "partition result ";
        for (int i = 0; i < num_subhnsw; i++)
            cout << space_size[i] << " ";
        cout << endl;

        for (int i = 0; i < num_subhnsw; i++){
            std::sort(partition_result[i].begin(), partition_result[i].end());
        }

        char buffer[5000];

        ifstream fin(base_file);

        cout << "ready to save" << endl;

        long long step = (long long) (ball.getDim() * sizeof(float) + sizeof(int));

        for(int i = 0; i < num_subhnsw; i++){
            ofstream fout(out_dir + "/subfile/partition" + std::to_string(i), std::ios::binary);
            for (int j = 0; j < partition_result[i].size(); j++){
                fin.seekg(step*partition_result[i][j], fin.beg);
                fin.read(reinterpret_cast<char*>(buffer), step);
                //int* id = (int*)(buffer + step);
                //*id = i;
                fout.write(buffer, step);
                //fout.write(reinterpret_cast<char*> (&i), sizeof(int));
            }
            fout.close();
        }
    }
}