#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    int k = 10;
    Graph* cube = new Graph();
    cube->gen_hypercube(k);
    // cube->display_adj();
    int flow = cube->max_flow();
    std::cout << "max flow: " << flow << std::endl;
}