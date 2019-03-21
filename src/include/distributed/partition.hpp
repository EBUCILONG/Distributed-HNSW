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
		vector<int> get_partition();
	};

	class PowerPartition : public Partition{

	};


	class SquarePartition : public Partition{

	};



}


