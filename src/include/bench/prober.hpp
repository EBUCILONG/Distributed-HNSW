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
using std::cout;
using std::endl;

#include "hnswlib/hnswalg.h"
#include "matrix.hpp"
#include "waker/waker.hpp"

namespace sm{
	class Prober{
	private:
		Waker* _waker;
		int _k;
		vector<hnswlib::HierarchicalNSW<float>*>* _hnsws;
		ss::Matrix<float>* _queries;
		vector<vector<pair<float, int > > > _answer;
	public:
		struct CompareByFirst {
			constexpr bool operator()(pair<float, int> const &a,
									  pair<float, int> const &b) const noexcept {
				return a.first > b.first;
			}
		};

		Prober(vector<hnswlib::HierarchicalNSW<float>*>* hnsws, ss::Matrix<float>* queries, int k, Waker* waker):
			_k(k), _hnsws(hnsws), _queries(queries), _waker(waker){
			_answer.resize(_queries->getSize());
		}

		vector<pair<float, int > > probe_query(int i){
			//cout << "1" << endl;
			vector<int> member = _waker->wakeUp(i, 100);
			//cout << "2" << endl;
			priority_queue<pair<float, int>, std::vector<pair<float, int > >, CompareByFirst> answer;
			//cout << "1" << endl;
			for (int j = 0; j < 10/*member.size()*/; j++){
				//cout << "2" << endl;
				//cout << "member: " << member[j] << endl;
				priority_queue<pair<float, long unsigned int >> result = _hnsws->operator [](j)->searchKnn(_queries->operator [](i), _k);
				//cout << "3" << endl;
				for (int k = 0; k < result.size(); k++){
					//cout << "4" << endl;
					const pair<float, long unsigned int>& p = result.top();
					float first = p.first;
					int second = (int) p.second;
					//cout << "5" << endl;
					answer.push(std::make_pair(first, second));
					result.pop();
				}
			}
			vector<pair<float, int > > returner;
			//cout << "finish for" << endl;
			for (int j = 0; j < _k; j++){
				returner.push_back(answer.top());
				answer.pop();
			}
			cout << endl;
			return returner;
		}

		vector<vector<pair<float, int > > > probe(){
			vector<vector<pair<float, int > > > returner;
			int sizer = _queries->getSize();
			for (int i = 0; i < sizer; i++){
				returner.push_back(probe_query(i));
			}
			return returner;
		}

	};





}
