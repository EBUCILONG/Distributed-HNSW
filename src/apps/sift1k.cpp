/*
 * sift1k.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: oruqimaru
 */


#include "executor.hpp"
#include "parameters.hpp"

#include <iostream>

int main(int argc, char** argv) {

    parameter para;
    LoadOptions(argc, argv, para);

    using DataType  = float;
    //using IndexType = ss::ITQIndex<DataType>;
    //using QueryType = ss::HammingRanker<DataType> ;

    SearchIterative<DataType>(para);
}

