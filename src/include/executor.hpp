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
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <omp.h>
#include <queue>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/errors.hpp>


#include <boost/format.hpp>

#include "bench/bencher.hpp"
#include "bench/prober.hpp"
#include "parameters.hpp"
#include "matrix.hpp"
#include "metric.hpp"
#include "utils/util.hpp"
#include "utils/cluster.hpp"
#include "hnswlib/hnswlib.h"
#include "hnswlib/space_l2.h"
#include "waker/waker.hpp"

using namespace std;
using namespace ss;

#define BASELINE 0

void LoadOptions(int argc, char **argv, parameter &para) {
    namespace po = boost::program_options;

    po::options_description opts("Allowed options");
    opts.add_options()
        ("help,h", "help info")
        ("num_bit,l",        po::value<int   >(&para.num_bit)         ->default_value(32)  , "num of hash bit")
        ("graph_K",          po::value<int   >(&para.graph_K)         ->default_value(50)  , "number of neighbors")
        // TODO(Xinyan): to support multi thread
        ("num_thread",       po::value<int   >(&para.num_thread)      ->default_value(1),    "num of thread")
        ("dim,d",            po::value<int   >(&para.dim)             ->default_value(-1),   "origin dimension of data")
        ("transformed_dim",  po::value<int   >(&para.transformed_dim) ->default_value(0)  ,  "origin dimension of data")
        ("num_sub_data_set", po::value<int   >(&para.num_sub_data_set)->default_value(-1),   "number of sub data set")
		("partition,p",      po::value<int   >(&para.partition)		  ->default_value(10),   "number of partition")
		("max_balance", 	 po::value<int   >(&para.max_balance)	  ->default_value(4),    "number of sub data set")
        ("r,r",              po::value<float >(&para.r)               ->default_value(2.5),  "float 'w' in e2lsh")
        ("kmeans_centers",   po::value<int   >(&para.kmeans_centers)  ->default_value(50),   "number of centers")
        ("num_codebook",     po::value<int   >(&para.num_codebook)    ->default_value(2),    "number of codebook")
        ("iteration,i",      po::value<int   >(&para.iteration)       ->default_value(10),   "training iterations")

        ("train_data,t",     po::value<string >(&para.train_data),                         "data for training")
        ("base_data,b",      po::value<string >(&para.base_data) ,                         "data stored in index")
        ("query_data,q",     po::value<string >(&para.query_data),                         "data for query")
        ("ground_truth,g",   po::value<string >(&para.ground_truth),                       "ground truth file")
        ("graph_knn",        po::value<string >(&para.graph_knn),                          "k nearest neighbors")
		//("codebook_file,cf", po::value<string >(&para.codebook_file),					   "code_books file for aq")
		//("encodes_file,ef",  po::value<string >(&para.encodes_file),					   "encodes file for aq")
		("out_dir,od",       po::value<string > (&para.out_dir),                            "the output dir for some in processing data")
        ("output_file,ef",   po::value<string >(&para.output_file),					       "output file for aq")
		("load_cluster",  	 po::value<int    >(&para.load_cluster),					   "indicator whether load clusters")
		("cluster_file,cf",  po::value<string >(&para.cluster_file),					   "cluster file")
  		("graph_file,x",     po::value<string >(&para.graph_file),                         "graph_file")
		("partition_file,s", po::value<string >(&para.partition_file),                     "partition_file")
		("hnsw_dir",         po::value<string >(&para.hnsw_dir),                           "hnsw directory")

    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << opts << endl;
        exit(0);
    }
}

template <class DataType/*, class IndexType, class QueryType, class MetricType=ss::EuclidMetric<DataType>*/ >
int SearchIterative(parameter &para) {
    ss::timer time_recorder;

    cout    << "#==============================================================================" << endl;
    cout    << "#==============================================================================" << endl;
    cout    << "#[loading ] loading ground truth " << endl;
    Bencher truth_bench(para.ground_truth.c_str());

    cout << "#[loading ] loading fvecs data                                    " ;
    time_recorder.restart();
    cout    << "#[loading ] loding base file from : " << para.train_data << endl;
    ss::Matrix<DataType> train_data(para.train_data);
    ss::Matrix<DataType> base_data (para.base_data);
    cout    << "#[loading ] loding query file from : " << para.query_data << endl;
    ss::Matrix<DataType> query_data(para.query_data);
    cout << "using time :" << time_recorder.elapsed() << endl;

    para.topK       = truth_bench.getTopK();
    para.train_size = train_data.getSize();
    para.base_size  = base_data.getSize();
    para.query_size = query_data.getSize();
    para.dim        = train_data.getDim() + para.transformed_dim; /// useful when add dimensions for some algorithm
    para.origin_dim = train_data.getDim();

    cout << "#[training ] preparing clusters" << endl;
    std::vector<sm::Cluster*>* clusters;
    std::vector<float> centroids;
    if (para.load_cluster){
    	clusters = sm::load_cluster(train_data, para.cluster_file, centroids);
    	if (clusters->size() != para.partition){
			cout << "#[error ]wrong num partition input in shell file" << endl;
			assert (false);
		}
    }
    else
    	clusters = sm::cluster_machine(train_data, para.output_file, para.partition,para.iteration, para.max_balance, centroids);

    cout << "#[temprory ] save centroids in: " << para.out_dir << "/centroids" << endl;
    std::ofstream wFile;
    wFile.open((para.out_dir + "/centroids").c_str());
    if (!wFile) {
                std::cout << "#[error ] cannot open file " << para.out_dir.c_str() << std::endl;
                assert(false);
            }
    wFile << para.partition << " " << para.dim << std::endl;
    for (int i = 0; i < para.partition * para.dim; i++)
    	wFile << centroids[i] << " ";
    wFile.close();

    cout << "#[training ] training hnsw on centroids" << endl;
    int vecdim = para.dim;
    float* mass = centroids.data();
    hnswlib::L2Space l2space(para.dim);
    hnswlib::HierarchicalNSW<float> appr_alg(&l2space, para.partition, 32, 500);
    for (int i = 0; i < 1; i++) {
            appr_alg.addPoint((void *) (mass + vecdim * i), (size_t) i);
        }
#pragma omp parallel for
	for (int i = 1; i < para.partition; i++) {
		appr_alg.addPoint((void *) (mass + vecdim * i), (size_t) i);
	}

	cout << "#[temprory ] save hnsw on centroids in: " << para.graph_file << endl;
    appr_alg.save_level_zero(para.graph_file);

    sm::Waker waker(para.partition, para.partition_file.c_str(), query_data, appr_alg, 10);

    const char * spliter = "||";
	cout << " k  " << spliter
		 << "aver"<<spliter
		 << " std" << endl;

    for (int i = 10; i <= 10; i += 10){
    	waker.testWake(i);
    	cout << i << " " << spliter
			 << waker.getAverWake() <<spliter
			 << waker.getStdWake()  << endl;
    }

    //TODO: change num machine to changable
    vector<hnswlib::HierarchicalNSW<float>* > hnsws;


    /*cout << "#[training ] prepare wake map" << endl;
    for (int i = 0; i < 10; i++){
    	vector<int> member = waker.getMember(i);
    	int max_size = 0;
    	for (int j = 0; j < member.size(); j++)
    		max_size += clusters->operator [](member[j])->get_size();
    	hnswlib::HierarchicalNSW<float>* new_hnsw = new hnswlib::HierarchicalNSW<float>(&l2space, max_size, 32, 500);
    	hnsws.push_back(new_hnsw);
    }

    cout << "#[training ] training sub hnsws" << endl;
#pragma omp parallel for
    for (int i = 0; i < 10; i++){
    	vector<int> member = waker.getMember(i);
    	for (int j = 0; j < member.size(); j++){
    		Cluster* candi = clusters->operator [](member[j]);
    		int sizer = candi->get_size();
    		for (int k = 0; k < sizer; k++){
    			hnsws[i]->addPoint(candi->operator [](k)->get_data(), candi->operator [](k)->get_index());
    		}
    	}
    }

    cout << "#[temporary ] saving sub hnsws" << endl;
    for (int i = 0; i < 10; i++){
    	hnsws[i]->saveIndex(para.out_dir + "/hnsw" + std::to_string(i));
    }*/

#if BASELINE == 1
    for (int i = 0; i < 10; i++){
		hnswlib::HierarchicalNSW<float>* new_hnsw = new hnswlib::HierarchicalNSW<float>(&l2space, train_data.getSize() / 10, 32, 500);
		hnsws.push_back(new_hnsw);
	}

	cout << "#[training ] training sub hnsws" << endl;
#pragma omp parallel for
	for (int i = 0; i < 10; i++){
		int sizer = train_data.getSize() / 10;
		for (int j = 0; j < sizer; j++){
			hnsws[i]->addPoint(train_data[i*sizer+j], i*sizer+j);
		}
	}

	cout << "#[temporary ] saving sub hnsws" << endl;
	for (int i = 0; i < 10; i++){
		hnsws[i]->saveIndex(para.out_dir + "/baseline" + "/hnsw" + std::to_string(i));
	}
#endif

#if BASELINE == 2
	hnswlib::HierarchicalNSW<float> hnsw(&l2space, para.train_size, 32, 500);
	cout << "train" << endl;
	for (int i = 0; i < 1; i++) {
		hnsw.addPoint((void *) train_data[i], (size_t) i);
	}
//#pragma omp parallel for
	for (int i = 1; i < para.train_size; i++) {
		hnsw.addPoint((void *) train_data[i], (size_t) i);
	}
	cout << "save" << endl;
	hnsw.saveIndex(para.out_dir + "/baseline" + "/hnswb");
	hnsw.setEf(100);
	cout << "query" << endl;
	vector<vector<pair<float, int > > >   current_topKb;
	for (int i = 0; i < para.query_size; i++){
		priority_queue<pair<float, long unsigned int >> result = hnsw.searchKnn(query_data[i], para.topK);
		vector<pair<float, int > > pusher;
		while(result.size()){
			pusher.push_back(std::make_pair(result.top().first, (int)result.top().second));
			result.pop();
		}
		current_topKb.push_back(pusher);
	}
	cout << "check" << endl;
	Bencher current_benchb(current_topKb, false);
	cout << truth_bench.avg_recall(current_benchb) << endl;
	return 1;
#endif


#if BASELINE == 1
    cout << "#[temporary ] loading sub hnsws" << endl;
	for (int i = 0; i < 10; i++){
		hnswlib::HierarchicalNSW<float>* new_hnsw = new hnswlib::HierarchicalNSW<float>(&l2space, para.out_dir + "/baseline" + "/hnsw" + std::to_string(i));
		new_hnsw->setEf(100);
		hnsws.push_back(new_hnsw);
	}
	Bencher current_bench(current_topK, true);

#endif

	cout << "#[temporary ] loading sub hnsws" << endl;
	for (int i = 0; i < 10; i++){
		hnswlib::HierarchicalNSW<float>* new_hnsw = new hnswlib::HierarchicalNSW<float>(&l2space, para.out_dir  + "/hnsw" + std::to_string(i));
		new_hnsw->setEf(100);
		hnsws.push_back(new_hnsw);
	}

    cout << "#[testing ] start query" << endl;
    sm::Prober prober = sm::Prober(&hnsws, &query_data, para.topK, &waker);
    cout << "#[testing ] start probe" << endl;
    vector<vector<pair<float, int > > >   current_topK = prober.probe();
    cout << "#[testing ] intial bench" << endl;
    Bencher current_bench(current_topK, true);

    cout << "#[temporary ] ready to output recall" << endl;

    cout << truth_bench.avg_recall(current_bench) << endl;

    //MetricType metric(para.origin_dim);

    /*cout << "#[training] initial the index." << endl;
    IndexType index(para);

    cout << "#[training] training the hash functions or models                 ";
    time_recorder.restart();
    /// train the model, generate random vectors if using LSH,
    /// learn the projection vectors if using learning to hash method.(PCAH, ITQ, SH ...)
    index.Train(train_data);
    cout << "using time :" << time_recorder.elapsed() << endl;

    cout << "#[training] put data into index                                   ";
    time_recorder.restart();
    /// add database items into index, using the information(e.g. hahs function) learned/generated in training stage.
    index.Add(base_data);
    cout << "using time :" << time_recorder.elapsed() << endl;


    vector<QueryType * >                  queries(para.query_size);
    for (int i = 0; i < para.query_size; i++) {
        /// determine the sequence of probing bucket(except probing by looking up)
        queries[i] = (new QueryType(&index, query_data[i], metric, base_data, para) );
    }

    ofstream output_dir(para.output_file);

    const char * spliter = ",";
    cout << "#==============================================================================" << endl;
    cout << "#==============================================================================" << endl;
    cout << "expected items" << spliter
         << "overall time" << spliter
         << "avg recall" << spliter
         << "avg precision" << spliter
         << "avg error" << spliter
         << "avg items"
         << "\n";
    output_dir << "expected items" << spliter
               << "overall time" << spliter
               << "avg recall" << "\n";

    time_recorder.restart();

    for (int num_items = 1; num_items / 2 < para.base_size; num_items *= 2 ) {

        if ( num_items > para.base_size )
            num_items = para.base_size;

        vector<vector<pair<float, int > > >   current_topK(para.query_size);    //TODO copy should be avoided
        vector<int >                          item_probed(para.query_size);

        {  /// probing

            for (int i = 0; i <  para.query_size; i++) {  /// probing
                /// probe more bucket util the number of probed item is no less than {$numItems}
                queries[i]->Precompute();
                queries[i]->Add_and_Sort();
                queries[i]->ProbeItems(num_items);
                item_probed[i]  = queries[i]->GetNumItemsProbed();
                current_topK[i] = queries[i]->GetSortedTopK();
            }

        }

        /// statistic such as recall, precision, probing time and probed items
        double timer_elapsed = time_recorder.elapsed();

        {
            Bencher current_bench(current_topK, true);
            cout << num_items                                                << spliter
                 << timer_elapsed                                            << spliter
                 << truth_bench.avg_recall(current_bench)                    << spliter
                 << truth_bench.avg_precision(current_bench, item_probed)    << spliter
                 << truth_bench.avg_error(current_bench)                     << spliter
                 << truth_bench.avg_items(item_probed)                       << "\n";

            output_dir << num_items                                                << spliter
                       << timer_elapsed                                            << spliter
                       << truth_bench.avg_recall(current_bench)                    << "\n";
        }

    }

    for (int i = 0; i < para.query_size; i++) {
        delete  queries[i];
    }*/

    return 0;
}
