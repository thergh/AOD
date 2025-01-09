#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    int k = 3;
    Hypercube* cube = new Hypercube(k);
    // cube->display_adj();
    std::cout << "done for k = " << k << std::endl;
    // std::cout << cube->capacities[{1, 2}];
    cube->max_flow();
}