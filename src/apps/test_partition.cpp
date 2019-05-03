#include "matrix.hpp"
#include "parameters.hpp"
#include "executor.hpp"
#include "distributed/partition.hpp"
#include "utils/util.hpp"
#include "hnswlib/hnswalg.h"

using std::cin;
using std::cout;


void save_map (string out_path, vector<int>& map, int num_partition){
    std::ofstream fout(out_path);
    fout << num_partition << " " << map.size() << std::endl;
    for (int i = 0; i < map.size(); i++)
        fout << map[i] << " ";
    fout.close();
}

int main(int argc, char** argv){
    string hnsw_path;
    string centroid_path;
    string save_path;
    cout << "hnsw_path: ";
    cin >> hnsw_path;
    cout << "centroid path: ";
    cin >> centroid_path;
    cout << "mapping save path: ";
    cin >> save_path;
    hnswlib::L2Space l2space(96);
    hnswlib::HierarchicalNSW<float> meta(&l2space, hnsw_path);
    mt::Partition partition(1);
    vector<vector<int> > graph;
    vector<vector<float>> centroids;
    int num_nodes = dhnsw::load_centroids(centroid_path, centroids);
    int num_edges = meta.getLevel0Graph(graph);
    vector<int> map = partition.getPartition(graph, centroids, num_edges, 10);
    save_map(save_path, map, 10);
}