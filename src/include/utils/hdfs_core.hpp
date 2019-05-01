/*
 * hdfs_core.hpp
 *
 *  Created on: 1 May 2019
 *      Author: oruqimaru
 */

#pragma once

#include <hdfs.h>

void hdfsReadExact(hdfsFS& fs, hdfsFile& file, char* buffer, tSize length){
	long long aim_len = length;
	char* aim_buffer = buffer;
	while (true){
		long long read_len = hdfsRead(fs, fin, (void*)aim_buffer, aim_len);
		if (real_len != aim_len){
			aim_len = aim_len - real_len;
			aim_buffer += real_len;
		}
		else
			break;
	}
}


