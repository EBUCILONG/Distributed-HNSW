////////////////////////////////////////////////////////////////////////////////
/// Copyright 2018-present Xinyan DAI<xinyan.dai@outlook.com>
///
/// permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to
/// deal in the Software without restriction, including without limitation the
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions ofthe Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

/// @version 0.1
/// @author  Xinyan DAI
/// @contact xinyan.dai@outlook.com
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cassert>

namespace ss {

    using std::vector;
    using std::pair;

    vector<float>* centroid_loader(ss::Matrix& datas, std::string inFile, bool save, std::string outFile = NULL){
    	std::ifstream rFile;
    	rFile.open(inFile.c_str());
    	int dimension = datas.getDim();
    	int numCluster = 0;
    	rFile >> numCluster;

    	vector<float>* centroid_data = new std::vector<float>;
    	centroid_data->reserve(numCluster * dimension);

    	for (int i = 0; i < numCluster; i++){
    		int sizer = 0;
    		rFile >> sizer;
    		rFile >> sizer;
    		vector<int> members;
			vector<float> centroid(dimension, 0);

    		for (int j = 0; j < sizer; j++){
    			int son = 0;
    			rFile >> son;
    			members.push_back(son);
    		}

    		for (int k = 0; k < sizer; k++){
				float* data = datas[members[i]];
				for (int j = 0; j < dimension; j++){
					centroid[j] += data[j];
				}
			}

    		for (int k = 0; k < dimension; k++)
    			centroid_data->push_back(centroid[k]/sizer);
    	}

    	rFile.close();

    	assert (centroid_data->size() == numCluster * dimension);

    	if (save){
    		std::ofstream wFile;
    		wFile.open(outFile.c_str());

    		wFile << numCluster << " " << dimension << std::endl;
        	for (int i = 0; i < numCluster * dimension; i++)
        		wFile << centroid_data->operator [](i) << " ";

        	wFile.close();
    	}

    	return &centroid_data;
    }

    template <typename FirstType, typename SencondType>
    void SortPairByFirst(vector<std::pair<FirstType, SencondType> > * _sorted_bucket) {
        std::sort(
                _sorted_bucket->begin(),
                _sorted_bucket->end(),
                [](const pair<FirstType, SencondType >& a, const pair<FirstType, SencondType>& b) {
                    if (a.first != b.first)
                        return a.first < b.first;
                    else
                        return a.second < b.second;
                });
    }

    template <typename FirstType, typename SencondType>
    void SortPairBySecond(vector<std::pair<FirstType, SencondType> > * _sorted_bucket) {
        std::sort(
                _sorted_bucket->begin(),
                _sorted_bucket->end(),
                [](const pair<FirstType, SencondType >& a, const pair<FirstType, SencondType>& b) {
                    if (a.second != b.second)
                        return a.second < b.second;
                    else
                        return a.first < b.first;
                });
    }


    template <class DataType >
    DataType inline InnerProduct(const DataType *a, const DataType *b, int dim) {

        DataType sum = .0;
        for (int i = 0; i < dim; ++i) {
            sum += a[i] * b[i];
        }
        return sum;
    }

    template <class DataType >
    	DataType inline IPDistance_Ary2Vec(const DataType *a, const vector<DataType> *b, int dim){
    	DataType sum = .0;
    	for (int i = 0; i < dim; ++i){
    		sum += a[i] * (*b)[i];
    	}
    	return sum;
    }


    template <class DataType>
    DataType inline CalculateNorm(const DataType *a, int dim) {
        return std::sqrt(InnerProduct(a, a, dim));
    }


    template <class DataType >
    DataType inline Cosine(const DataType *a, const DataType *b, int dim) {
        return InnerProduct(a, b, dim) / static_cast<double >(CalculateNorm(a, dim)) / CalculateNorm(b, dim);
    }


    template <class DataType>
    DataType inline DiffProduct(const DataType *a, const DataType *means, const DataType *b, int dim) {
    
        DataType sum = .0;
        for (int i = 0; i < dim; ++i) {
            sum += (a[i] - means[i]) * b[i];
        }
        return sum;
    }


    template <class DataType >
    DataType inline EuclidDistance(const DataType *a, const DataType *b, int dim) {

        DataType sum = .0;
        for (int i = 0; i < dim; ++i) {
            sum += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(sum);
    }

    template <class DataType >
	DataType inline EuclidDistance_Ary2Vec(const DataType *a, const vector<DataType> *b, int dim) {

		DataType sum = .0;
		for (int i = 0; i < dim; ++i) {
			sum += (a[i] - b->operator [](i)) * (a[i] - b->operator [](i));
		}
		return sqrt(sum);
	}

    template <class DataType >
    DataType inline AngularDistance(const DataType *a, const DataType *b, int dim) {
        return std::acos(Cosine(a, b, dim));
    }

    template <class DataType >
    DataType inline InnerProductDistance(const DataType *a, const DataType *b, int dim) {
        return - InnerProduct(a, b, dim);
    }


    template <class DataType>
    void inline ScaleData(DataType *target, const DataType *data, DataType scale, int dim) {
        for (int d = 0; d<dim; d++) {
            target[d] = data[d] / scale;
        }
    }


    template <class DataType>
    void inline Normalize(DataType *data, int dim) {
        ScaleData(data, data, CalculateNorm(data, dim), dim);
    }

    int inline CountBitOne(uint64_t xorval) {
        int count = 0;

        while(xorval != 0) {
            count++;
            xorval &= (xorval-1);
        }
        return count;
    }

    template <class DataType >
    int inline CountDiff(const DataType *a, const DataType *b, int dim) {
        int count = 0;
        for (int d=0; d<dim; d++) {
            if (a[d]!=b[d]) {
                count++;
            }
        }
        return count;
    }

} // namespace ss
