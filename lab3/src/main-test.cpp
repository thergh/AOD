#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>

#include "algo.hpp"


void print_vector(std::vector<int> v){
    std::cout << "[ ";
    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << "]\n";
}


int main(){
    std::string graph_file = "data/Long-C.0.0.gr";
    // std::string graph_file = "data/plik_z_danymi.gr";
    Graph* g = new Graph(graph_file);
    // g->print_graph();
    // g->p2p_from_file("data/pary.p2p");
    auto distances = g->dijkstra(0);
    print_vector(distances);
}