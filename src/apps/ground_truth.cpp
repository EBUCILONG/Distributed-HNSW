#include "utils/ground_truth.hpp"
#include "metric.hpp"
#include "matrix.hpp"
#include <string>
#include <omp.h>

using std::string;

int main(int argc, char** argv) {
    string base_file(argv[1]);
    string query_file(argv[2]);
    int K = std::stoi(argv[3]);
    string output_lshbox(argv[4]);
    string output_idvecs(argv[5]);
    int num_threads = std::stoi(argv[6]);

    omp_set_num_threads(num_threads);

    ss::Matrix<float> base_vecs(base_file);
    ss::Matrix<float> query_vecs(query_file);

    vector<vector<MaxHeapElement<int> > > knn =
            ss::ExactKNN<float>(query_vecs.getData(), query_vecs.getSize(), base_vecs.getData(),
                    base_vecs.getSize(), base_vecs.getDim(), K, ss::EuclidDistance<float>);
    ss::GroundWriter::WriteIVECS<float>(output_idvecs.c_str(), knn);
    ss::GroundWriter::WriteLSHBOX<float>(output_lshbox.c_str(), knn);
    return 0;
}