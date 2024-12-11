#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>

#include "algo.hpp"



int main(){
    // std::string graph_file = "data/Long-C.0.0.gr";
    // std::string graph_file = "data/plik_z_danymi.gr";
    // std::string ss_file = "data/zrodla.ss";
    // std::string p2p_file = "data/pary.p2p";
    std::string graph_file = "ch9-1.1/docs/format/samples/sample-c.gr.txt";

    Graph* g = new Graph(graph_file);

    std::string result_path = "results/mock_res.txt";

    auto d_dijkstra = g->dijkstra(0);

    auto d_radix = g->radix(0);
    // auto d_radix = g->radixheap(0);
    print_vector(d_dijkstra);
    print_vector(d_radix);
    // print_vector(distances2);


    // auto distances3 = g->radixheap(0);
    // print_vector(distances3);
}

