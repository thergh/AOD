#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    int k = 12;
    int i = 12;
    Graph* cube = new Graph();
    // cube->gen_hypercube(k);
    cube->gen_bipartite(k, i);
    // cube->display_adj();
    int flow = cube->max_flow();
    std::cout << "max flow: " << flow << std::endl;
}