#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    int k = 4;
    int i = 4;
    Graph* cube = new Graph();
    // cube->gen_hypercube(k);
    cube->gen_bipartite(k, i);
    // cube->display_adj();
    int flow = cube->max_flow();
    std::cout << "max flow: " << flow << std::endl;
    std::cout << "paths: " << cube->path_count << std::endl;
    std::cout << "time: " << cube->alg_time << std::endl;
}