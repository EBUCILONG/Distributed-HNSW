/*
 * cluster.hpp
 *
 *  Created on: 20 Feb 2019
 *      Author: oruqimaru
 */

#pragma once

#include <omp.h>

#include <float.h>
#include <assert.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

#include "matrix.hpp"
#include "metric.hpp"
#include "utils/calculator.hpp"

#define NOTASSIGNED -0x978
#define NOTKNOWN -0x246

typedef enum ClusterType {
	Binary,
	Balance
} clusterType;

using std::cin;
using std::cout;
using std::vector;
using std::endl;


namespace sm{

	class Cluster;

	class Point{
		int _dimension;
		float *_data;
		int _clusterId;
		int _index;

	public:
		explicit Point(int index, int dimension): _dimension(dimension),
			_index(index), _clusterId(NOTASSIGNED), _data(NULL){
		}

		float operator [] (int i) const {
			if (i >= _dimension){
				cout << "Point error: data access out of order" << endl;
				assert(0);
			}
			return *(_data + i);/// i * dimension may overflow int
		}

		float * get_data(){
			return _data;
		}

		void set_data(float* data){
			_data = data;
		}

		void set_cluster(int clusterId){
			_clusterId = clusterId;
		}

		int get_dimension(){
			return _dimension;
		}

		int get_index(){
			return _index;
		}

		float L2_dist (vector<float> * centre){
			return ss::EuclidDistance_Ary2Vec(_data, centre, _dimension);
		}

		void assign_cluster (vector<Cluster*> *clusters){
			int label = -1;
			float dister = FLT_MAX;
			int size = clusters->size();
			for (int i = 0; i < size; i++){
				float dist = L2_dist (clusters->at(i)->get_centroid());
				if (dist < dister){
					label = i;
					dister = dist;
				}
			}
			clusters->at(label)->append_point(this);
		}

	};

	class Cluster{
		vector <Point *> _datas;
		vector <float> _centroid;
		int _size;
		int _dimension;
		int _aimSize;
		int _aimNPartition;
		clusterType _cType;
		bool _done;

		// parallel thing
		omp_lock_t _appendLock;

		vector<Cluster*> _childrens;
	public:
		explicit Cluster (int dimension, float* centre): _size(0),
			_aimSize(NOTKNOWN), _aimNPartition(NOTKNOWN), _dimension(dimension), _done (false){
			_centroid.resize(_dimension);
			set_centroid (centre);
			omp_init_lock(&_appendLock);
		}

		Point * operator [] (int i) const {
			if (i >= _size){
				cout << "Cluster error: data access out of bound" << endl;
				assert(0);
			}
			return _datas[i];/// i * dimension may overflow int
		}

		void append_point(Point* point){
			omp_set_lock (&_appendLock);
			_datas.push_back(point);
			_size++;
			omp_unset_lock (&_appendLock);
		}

		void set_centroid (float* centre){
			for (int i = 0; i < _dimension; i++)
				_centroid[i] = centre[i];
		}

		void update_centroid(){
			for (int i = 0; i < _dimension; i++)
				_centroid[i] = 0;
			for (int i = 0; i < _size; i++){
				float * appender = _datas[i]->get_data();
				for(int j = 0; j < _dimension; j++){
					_centroid[j] += appender[j] / _size;
				}
			}
		}

		void cluster_binary (int iteration){
			Cluster c1 = new Cluster(_dimension, _datas[0]->get_data());
			Cluster c2 = new Cluster(_dimension, _datas[1]->get_data());
			_childrens.push_back(& c1);
			_childrens.push_back(& c2);

			for (int i = 0; i < iteration; i++){
#pragma omp parallel for
				for(int j = 0; j < _size; j++){
					_datas[j]->assign_cluster(&_childrens);
				}

#pragma omp parallel for
				for(int j = 0; j < _childrens.size(); j++){
					_childrens[j]->update_centroid();
					_childrens[j]->reset_data();
				}
			}

			/*
			 * 一共要分为 x 分，第一个有size1， 第二个有size2
			 *
			 */
			float numPCluster = (float)_size / (float)_aimNPartition;
			int aim1 = (int) round((float)_childrens[0]->get_size() / numPCluster);
			_childrens[0]->set_aimNPartition(_aimNPartition - aim1);
		}

		void set_aimNPartition(int num){
			_aimNPartition = num;
		}

		vector<float> * get_centroid(){
			return &_centroid;
		}

		int get_size (){
			return _size;
		}

		int get_aim_size(){
			return _aimSize;
		}

		int get_aim_partition(){
			return _aimNPartition;
		}

		int get_dimension (){
			return _dimension;
		}

		int done_or_not (){
			return _done;
		}

		void reset_data (){
			_size = 0;
			_datas.resize(0);
		}
	};



}



