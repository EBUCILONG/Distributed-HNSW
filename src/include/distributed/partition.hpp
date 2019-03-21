/*
 * partition.hpp
 *
 *  Created on: 21 Mar 2019
 *      Author: oruqimaru
 */

#pragma once

#include <vector>
#include <string>

using std::vector;

namespace mt{
	class Partition{
	public:
		Partition(int mode);
		vector<int> get_partition(vector<vector<int> > graph, vector<vector<float> > centroids, int num_edges);
	};

	class PowerPartition : public Partition{

	};

	class SquarePartition : public Partition{

	};



}


