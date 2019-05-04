#include "matrix.hpp"
#include "parameters.hpp"
#include "executor.hpp"
#include "distributed/partition.hpp"
#include "utils/util.hpp"
#include "hnswlib/hnswalg.h"

using std::cin;
using std::cout;
using std::endl;


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
    cout << "Getting hnsw" << endl;
    hnswlib::L2Space l2space(96);
    hnswlib::HierarchicalNSW<float> meta(&l2space, hnsw_path);
    cout << "Loaded HNSW, blocking..." << endl;
    cout << "Press any key to exit" << endl;
    getchar();
}