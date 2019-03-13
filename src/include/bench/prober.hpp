/*
 * prober.hpp
 *
 *  Created on: 13 Mar 2019
 *      Author: oruqimaru
 */


#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <queue>

using std::vector;
using std::priority_queue;
using std::pair;

#include "hnswlib/hnswalg.h"
#include "matrix.hpp"

namespace sm{
	class Prober{
	private:
		int _k;
		vector<hnswlib::HierarchicalNSW<float>*>* _hnsws;
		ss::Matrix* _queries;
		vector<vector<pair<float, int > > > _answer;
	public:
		struct CompareByFirst {
			constexpr bool operator()(pair<float, int> const &a,
									  pair<float, int> const &b) const noexcept {
				return a.first < b.first;
			}
		};

		Prober(vector<hnswlib::HierarchicalNSW<float>*>* hnsws, ss::Matrix* queries, int k):
			_k(k), _hnsws(hnsws), _queries(queries){
			_answer.resize(_queries->getSize());
		}

		vector<pair<float, int > > probe_query(int i){
			priority_queue<pair<float, int>, std::vector<pair<float, int > >, CompareByFirst> answer;
			for (int j = 0; j < _hnsws->size(); j++){
				priority_queue<pair<float, int >> result = _hnsws->operator [](j)->searchKnn(_queries->operator [](i), _k);
				for (int k = 0; k < result.size(); k++){
					answer.push(result.top());
					result.pop();
				}
			}
			vector<pair<float, int > > returner;
			for (int j = 0; j < _k; j++){
				returner.push_back(answer.top());
				answer.pop();
			}
			return returner;
		}

		vector<vector<pair<float, int > > > probe(){
			vector<vector<pair<float, int > > > returner;
			int sizer = _queries->getSize();
			returner.resize(sizer);
			for (int i = 0; i < sizer; i++)
				returner.push_back(probe_query(i));
			return returner;
		}

	};





}
