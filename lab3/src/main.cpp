/**
 * TODO:
 * czytanie danych z plików podanych w inpucie
 * zwracanie wyników w odpowiednim formacie
 * zapisywanie wyników
 * zrobić strukturę algorytmów w headerze
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>
#include <chrono>


#include "algo.hpp"

void print_vector(std::vector<int> v){
    std::cout << "[ ";
    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << "]\n";
}



/**
 * Returns 1 if there is an error in the arguments, 0 otherwise
 */
int check_arguments(int argc, char *argv[]){
    if(argc != 8){ // Wrong number of arguments
        std::cout << "Error: Wrong number of arguments." << "\n";
        return 1;
    }
    if(std::string(argv[1]) != "dijkstra" && std::string(argv[1]) != "dial" && std::string(argv[1]) != "radixheap"){
        std::cout << "Error: Argument number 1 must be 'dijkstra' or 'dial' or 'radixheap'" << "\n";
        std::cout << "argv[1]: " << argv[1] << std::endl;
        return 1;
    }    
    if(std::string(argv[2]) != "-d"){ // First argument is always the same
        std::cout << "Error: Argument number 2 must be '-d'" << "\n";
        return 1;
    }
    if(std::string(argv[4]) != "-ss" && std::string(argv[4]) != "-p2p"){
        std::cout << "Error: Argument number 4 must be '-ss' or '-p2p'" << "\n";
        return 1;
    }
    if(std::string(argv[6]) != "-oss" && std::string(argv[6]) != "-op2p"){
        std::cout << "Error: Argument number 6 must be '-oss' or '-op2p'" << "\n";
        return 1;
    }
    if(std::string(argv[4]) == "-ss" && std::string(argv[6]) != "-oss"){
        std::cout << "Error: Argument number 6 must be '-oss' to match argument 4: '-ss" << "\n";
        return 1;
    }
    if(std::string(argv[4]) == "-p2p" && std::string(argv[6]) != "-op2p"){
        std::cout << "Error: Argument number 6 must be '-op2p' to match argument 4: '-p2p" << "\n";
        return 1;
    }
    if(!(std::filesystem::exists(std::string(argv[3])))){
        std::cout << "Error: File path provided in argument 3 doesn't exist." << "\n";
    }
    if(!(std::string(argv[3]).ends_with(".gr"))){
        std::cout << "Error: File provided in argument 3 has wrong file format. Required format: .gr" << "\n";
    }
    if(std::string(argv[4]) == "-ss" && !(std::string(argv[5]).ends_with(".ss"))){
        std::cout << "Error: File provided in argument 5 has wrong file format. Format must match argument 4: .ss" << "\n";
    }
    if(std::string(argv[4]) == "-p2p" && !(std::string(argv[5]).ends_with(".p2p"))){
        std::cout << "Error: File provided in argument 5 has wrong file format. Format must match argument 4: .p2p" << "\n";
    }




    return 0;
}


enum Algorithm{
    DIJKSTRA,
    DIAL,
    RADIXHEAP
};


enum Mode{
    SS,
    P2P
};


int main(int argc, char *argv[]){
    if(check_arguments(argc, argv)){ // Something's wrong with arguments
        return 1;
    }

    // Setting algorithm
    Algorithm alg;
    if(std::string(argv[1]) == "dijkstra"){
        alg = DIJKSTRA;
    }
    else if(std::string(argv[1]) == "dial"){
        alg = DIAL;
    }
    else if(std::string(argv[1]) == "radixheap"){
        alg = RADIXHEAP;
    }

    // Setting mode
    Mode mode;
    if(std::string(argv[4]) == "-ss"){
        mode = SS;
    }
    else if(std::string(argv[4]) == "-p2p"){
        mode = P2P;
    }

    const int MAX_INT = std::numeric_limits<int>::max();
    
    std::string graph_path = argv[3];
    std::string source_path = argv[5];
    std::string result_path = "results/main-res.txt";

    Graph* g = new Graph(graph_path);
    g->print_graph();
    // print_vector(g->ss_from_file(ss_file));

    if(mode == SS){
        std::vector<int> sources = g->ss_from_file(source_path);

        std::cout << "sources: ";
        print_vector(sources);

        for(const auto& s : sources){
            std::vector<int> distances;

            // int time_ms = 0.0;
            int min_dist = MAX_INT;
            int max_dist = 0;

            auto start_time = std::chrono::high_resolution_clock::now();



            if(alg == DIJKSTRA){
                distances = g->dijkstra(s);
                std::cout << "performed DIJKSTRA algorithm\n";
            }
            else if(alg == DIAL){
                distances = g->dial(s);
                std::cout << "performed DIAL algorithm\n";
            }
            else if(alg == RADIXHEAP){ // TODO: not implemented
                distances = g->radixheap(s);
            }

            for(const auto& d : distances){
                if(d > max_dist){
                    max_dist = d;
                }
                if(d < min_dist){
                    min_dist = d;
                }
            }
            std::cout << "distances: ";
            print_vector(distances);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
            auto time_ms = time_diff.count() / 1000; // casting to ms in int

            std::cout << "source: " << s << " min: " << min_dist << " max: " << max_dist << " time: " << time_ms << std::endl;
            
        }

    }





    return 0;
};