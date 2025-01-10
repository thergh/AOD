#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    // ./hypercube --size k --printFlow
    int k = std::stoi(argv[2]);
    bool printFlow;
    if(argc == 4){
        if(argv[3] == "--printFlow"){
            printFlow = true;
        }
        else{
            printFlow = false;
        }
    }

    int k = 12;
    int i = 12;

    Graph* cube = new Graph();
    // cube->gen_hypercube(k);
    // cube->gen_bipartite(k, i);
    // cube->display_adj();
    int flow = cube->max_flow();
    std::cout << "max flow: " << flow << std::endl;
}