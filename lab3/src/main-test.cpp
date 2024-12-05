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
    // std::string graph_file = "data/Long-C.0.0.gr";
    std::string graph_file = "data/plik_z_danymi.gr";
    std::string ss_file = "data/zrodla.ss";
    std::string p2p_file = "data/pary.p2p";

    Graph* g = new Graph(graph_file);
    print_vector(g->ss_from_file(ss_file));

    std::string result_path = "results/mock_res.txt";
    // g->ss_result(g->V, g->E, {-1, -1}, -0.0, graph_file, ss_file, result_path);
    g->p2p_result(g->V, g->E, {{1, 2, 3}}, {-1, -1}, -0.0, graph_file, p2p_file, result_path);

    // g->p2p_from_file("data/pary.p2p");
    // auto distances1 = g->dijkstra(0);
    // print_vector(distances1);
    // auto distances2 = g->dial(0);
    // print_vector(distances2);


    // auto distances3 = g->radixheap(0);
    // print_vector(distances3);
}