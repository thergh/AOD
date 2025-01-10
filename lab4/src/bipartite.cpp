#include <iostream>

#include "algo.hpp"


int main(int argc, char* argv[]){

    // ./bipartite --size 8 --degree 6 --printMatching
    
    int k = std::stoi(argv[2]);
    int i = std::stoi(argv[4]);
    bool printMatching;
    if(argc == 6){
        printMatching = true;
    }
    else{
        printMatching = false;
    }

    Graph* bip = new Graph();
    bip->gen_bipartite(k, i);
    int flow = bip->max_flow();

    std::cout << "max matching: " << flow << std::endl;
    if(printMatching){
        std::cout << "matched edges:" << std::endl;
        bip->display_matching();
    }

    std::cerr << "time: " << bip->alg_time << std::endl;
}