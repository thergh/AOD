#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>
#include <fstream>
#include <random>

#include "algo.hpp"



int time_diff(std::chrono::_V2::system_clock::time_point start_time){
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
    return time_diff.count();
}


template <typename T>
void v_to_file(const std::vector<T>& v, std::string output_path){
    std::ofstream ofs;
    ofs.open(output_path, std::ios_base::app);
    if(!ofs.is_open()){
        std::cout << "Error: Result file not open\n";
        return;
    }
    else{
        for(const auto& x : v){
            ofs << x << " ";
        }
        ofs << std::endl;
        ofs.close();
    }
}


std::vector<int> comp_dist(std::string input_path, int source){
    Graph* g = new Graph(input_path);
    int end = g->V - 1;
    auto v_dijkstra = g->dijkstra(source);
    auto v_dial = g->dial(source);
    auto v_radix = g->radix(source);
    int dist_dijkstra = v_dijkstra[end];
    int dist_dial = v_dial[end];
    int dist_radix = v_radix[end];
    return {dist_dijkstra, dist_dial, dist_radix};
}


std::vector<int> comp_dist_rnd(std::string input_path, int iterations);

std::vector<int> comp_time(std::string input_path, int source){
    std::chrono::_V2::system_clock::time_point start_time;
    Graph* g = new Graph(input_path);

    start_time = std::chrono::high_resolution_clock::now();
    g->dijkstra(source);
    auto dijkstra_time = time_diff(start_time);

    start_time = std::chrono::high_resolution_clock::now();
    auto v_dial = g->dial(source);
    auto dial_time = time_diff(start_time);

    start_time = std::chrono::high_resolution_clock::now();
    auto v_radix = g->radix(source);
    auto radix_time = time_diff(start_time);


    return {dijkstra_time, dial_time, radix_time};
}

std::vector<int> comp_time_rnd(std::string input_path, int iterations);



int main(){
    // print_vector(compare_algos_dist(1, "ch9-1.1/docs/format/samples/sample-c.gr.txt"));
    // print_vector(compare_algos_dist(1, "ch9-1.1/inputs/Square-n/Square-n.10.0.gr"));
    // compare_algos_dist(1, "ch9-1.1/inputs/Square-n/Square-n.10.0.gr");
    // run_dist();

    std::string input_path = "ch9-1.1/inputs/Long-n/Long-n.11.0.gr";
    print_vector(comp_dist(input_path, 0));
    print_vector(comp_time(input_path, 0));

    // v_to_file(v, "teck-res.txt");

    // std::cout << time << std::endl;
}