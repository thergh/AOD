#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    // ./hypercube --size 8 --printFlow
    
    int k = std::stoi(argv[2]);
    bool printFlow;
    if(argc == 4){
        printFlow = true;
    }
    else{
        printFlow = false;
    }

    Graph* cube = new Graph();
    cube->gen_hypercube(k);
    int flow = cube->max_flow();

    std::cout << "max flow: " << flow << std::endl;
    if(printFlow){
        std::cout << "flows:" << std::endl;
        cube->display_flow();
    }

    std::cerr << "time: " << cube->alg_time << std::endl;
    std::cerr << "augmenting path count: " << cube->path_count << std::endl;
}