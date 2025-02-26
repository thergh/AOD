#include "graph_alg.hpp"
#include <iostream>
#include <chrono>

// // TODO: stack limit on test 6
// int main(int argc, char *argv[]){
//     if(argc < 2){
//         std::cout << "Error: wrong arguments\n";
//         return 1;
//     }

//     std::string test_path = argv[1];
//     std::vector<std::vector<int>> graph = graph_from_file(test_path);

//     auto start = std::chrono::steady_clock::now();
//     auto result = SCC(graph);
//     auto end = std::chrono::steady_clock::now();
//     auto time_taken = end - start;
    
//     std::cout << "Number of SCC: " << result.size() << std::endl;
//     std::cout << "Number of vertices of each SCC: " << std::endl;
//     for(int i=0; i<result.size(); i++){
//         std::cout << result[i].size() << std::endl;
//     }
//     std::cout << std::endl;

//     if(graph.size() <= 200){
//         std::cout << "Strongly connected components: " << std::endl;
//         for(int i=0; i<result.size(); i++){
//             PrintVectorInt(result[i]);
//         }
//     }

//     std::cout << std::chrono::duration<double,
//         std::milli>(time_taken).count() << " ms" << std::endl;
// }


int main(int argc, char *argv[]){

    std::vector<std::vector<int>> graph = graph_from_file("tests/3/g3-1.txt");
    auto result = SCC(graph);

}