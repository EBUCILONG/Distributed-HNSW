#include "matrix.hpp"
#include "parameters.hpp"
#include "executor.hpp"
#include "distributed/partition.hpp"
#include "utils/util.hpp"
#include "hnswlib/hnswalg.h"

using std::cin;
using std::cout;

int main(int argc, char** argv){
    string hnsw_path;
    string centroid_path;
    cout << "hnsw_path: ";
    cin >> hnsw_path;
    cout << "centroid path: ";
    cin >> centroid_path;
    hnswlib::L2Space l2space(96);
    hnswlib::HierarchicalNSW<float> meta(&l2space, hnsw_path);
    mt::Partition partition(1);
    vector<vector<int> > graph;
    vector<vector<float>> centroids;
    int num_nodes = dhnsw::load_centroids(centroid_path, centroids);
    int num_edges = meta.getLevel0Graph(graph);
    vector<int> map = partition.getPartition(graph, centroids, num_edges, 10);
}