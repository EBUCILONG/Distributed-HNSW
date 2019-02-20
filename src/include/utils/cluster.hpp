/*
 * cluster.hpp
 *
 *  Created on: 20 Feb 2019
 *      Author: oruqimaru
 */

#pragma once

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

		void assign_cluster(int clusterId){
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

		int assign_cluster (vector<Cluster*> clusters){
			int label = -1;
			float dister = FLT_MAX;
			int size = clusters.size();
			for (int i = 0; i < size; i++){
				float dist = L2_dist (clusters[i]->get_centroid());
				if (dist < dister){
					label = i;
					dister = dist;
				}
			}
			return label;
		}

	};

	class Cluster{
		vector <Point *> _datas;
		vector <float> _centroid;
		int _size;
		int _dimension;
		int _aimSize;
		int _aimNPartition;
		bool _done;

	public:
		explicit Cluster (int dimension, int aimSize, int aimNPartition, float* centre): _size(0),
			_aimSize(aimSize), _aimNPartition(aimNPartition), _dimension(dimension), _done (false){
			_centroid.resize(_dimension);
			set_centroid (centre);
		}

		Point * operator [] (int i) const {
			if (i >= _size){
				cout << "Cluster error: data access out of bound" << endl;
				assert(0);
			}
			return _datas[i];/// i * dimension may overflow int
		}

		void append_point(Point* point){
			_datas.push_back(point);
			_size++;
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



