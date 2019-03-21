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
		vector<int> getPartition(vector<vector<int> >& graph, vector<vector<float> >& centroids, int num_edges, int num_partition);
	};

	class PowerPartition : public Partition{

	};

	class SquarePartition : public Partition{

	};



}


