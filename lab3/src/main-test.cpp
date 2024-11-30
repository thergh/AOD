#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>

#include "algo.hpp"


int main(){
    // std::string graph_file = "data/Long-C.0.0.gr";
    std::string graph_file = "data/plik_z_danymi.gr";
    Graph* g = new Graph(graph_file);
    // g->print_graph();
    // g->p2p_from_file("data/pary.p2p");
    g->dijkstra(0);
}