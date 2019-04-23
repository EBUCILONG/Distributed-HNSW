//
// Created by Oruqimaru on 22/4/2019.
//

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>

using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;

int main(int argc, char *argv[]){
    string input_path(argv[1]);
    string output_path(argv[2]);
    int dimension = atoi(argv[3]);
    int origin_size = atoi(argv[4]);
    int aim_size = atoi(argv[5]);

    char buffer[1000];

    std::srand ( unsigned ( std::time(0) ) );
    vector<int> shuffle;
    for (int i = 0; i < origin_size; i++)
        shuffle.push_back(i);

    std::random_shuffle (shuffle.begin(), shuffle.end());
    shuffle.erase(shuffle.end() + aim_size - origin_size, shuffle.end());
    std::sort(shuffle.begin(), shuffle.end());
    assert(shuffle.size() == aim_size);

    ifstream fin(input_path, std::ios::binary);
    ofstream fout (output_path, std::ios::binary);

    long long step = (long long) (dimension * sizeof(float) + sizeof(int));

    for(int i = 0; i < aim_size; i++){
        fin.seekg(step*shuffle[i], fin.beg);
        fin.read(reinterpret_cast<char*>(buffer), step);
        int* id = (int*)(buffer + step);
        *id = i;
        fout.write(buffer, step + sizeof(int));
    }


}