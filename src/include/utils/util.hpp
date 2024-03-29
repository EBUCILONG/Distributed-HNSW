//////////////////////////////////////////////////////////////////////////////
/// Copyright 2018-present Xinyan DAI<xinyan.dai@outlook.com>
///
/// permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
/// documentation files (the "Software"), to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
/// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
/// the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
/// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
/// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

/// @version 0.1
/// @author  Xinyan DAI
/// @contact xinyan.dai@outlook.com
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using std::vector;
using std::string;
using std::ifstream;

namespace dhnsw{
	void getIdvecsInfo(const string& path, int& dimension, int& size){
		std::ifstream fin(path.c_str(), std::ios::binary | std::ios::ate);
		if (!fin) {
			std::cout << "cannot open file " << path.c_str() << std::endl;
			assert(false);
		}
		uint64_t fileSize = fin.tellg();
		fin.seekg(0, fin.beg);
		assert(fileSize != 0);

		int dim;
		fin.read(reinterpret_cast<char*>(&dim), sizeof(int));
		std::cout << "dimension" << dim << std::endl;
		unsigned step = dim * sizeof(float) + 4 + 4;
		assert(fileSize % step == 0);
		uint64_t cardinality = fileSize / step;
		dimension = dim;
		size = (int) cardinality;
		fin.close();
	}

	int load_partition_map(string map_path, vector<int>& map){
		int total_partition;
		ifstream fin(map_path);
		fin >> total_partition;
		int iter, buffer;
		fin >> iter;
		for (int i = 0; i < iter; i++){
			fin >> buffer;
			map.push_back(buffer);
		}
		return total_partition;
	}

	int load_centroids(string centroid_path, vector<vector<float>>& centroid) {
	    ifstream fin(centroid_path);
	    int dimension, total_num;
	    fin >> dimension >> total_num;
	    for(int i=0; i< total_num; i++){
	        vector<float> vec;
	        for(int j=0; j< dimension; j++) {
	            float val;
	            fin >> val;
	            vec.push_back(val);
	        }
	        centroid.push_back(vec);
	    }
	    return total_num;
	}

	float avg(vector<int>& data){
		float result = 0;
		for(auto& elem:data){
			result+=elem;
		}
		result /= data.size();
		return result;
	}

	long long avg(vector<long long>& data){
		float result = 0;
		for(auto& elem:data){
			result+=elem;
		}
		result /= data.size();
		return result;
	}

	float stv(vector<int>& data){
		float aver = avg(data);
		float result = 0;
		for(auto& elem:data){
			result+=((float)elem - aver) * ((float)elem - aver);
		}
		return (float) sqrt(result / data.size());
	}
}

namespace ss {

    /**
     * A timer object measures elapsed time, and it is very similar to boost::timer.
     */
    class timer {
    public:
        timer(): time(static_cast<double>(clock())) {}
        ~timer() {}

        /**
         * Restart the timer.
         */
        void restart() {
            time = static_cast<double>(clock());
        }
        /**
         * Measures elapsed time.
         * @return The elapsed time
         */
        double elapsed() {
            return (static_cast<double>(clock()) - time) / CLOCKS_PER_SEC;
        }
    private:
        double time;
    };

}  // namespace ss
