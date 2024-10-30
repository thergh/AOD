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
    auto result = BFS(graph);
    auto end = std::chrono::steady_clock::now();
    auto time_taken = end - start;

    PrintVectorInt(result.first);
    std::cout << std::endl;

    if(argc == 3){
        print_parents(result.second);
    }

    std::cout << std::chrono::duration<double,
        std::milli>(time_taken).count() << " ms" << std::endl;
}