#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    int k = 14;
    Hypercube* cube = new Hypercube(k);
    // cube->display_adj();
    std::cout << "done for k = " << k << std::endl;
    // std::cout << cube->capacities[{1, 2}];
    int flow = cube->max_flow();
    std::cout << "max flow: " << flow << std::endl;
}