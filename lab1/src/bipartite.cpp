#include "graph_alg.hpp"
#include <iostream>
#include <chrono>


int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "Error: wrong arguments\n";
        return 1;
    }

    std::string test_path = argv[1];
    std::vector<std::vector<int>> graph = graph_from_file(test_path);

    auto start = std::chrono::steady_clock::now();
    auto result = bipartition(graph);
    auto end = std::chrono::steady_clock::now();
    auto time_taken = end - start;
    
    
    std::cout << "Is the graph bipartite? " << result.first << std::endl;
    std::cout << std::endl;

    if(graph.size() <= 200 && result.first == 1){
        std::cout << "First partition:\n";
        PrintVectorInt(result.second.first);
        std::cout << "Second partition:\n";
        PrintVectorInt(result.second.second);
    }

    std::cout << std::chrono::duration<double,
        std::milli>(time_taken).count() << " ms" << std::endl;
}