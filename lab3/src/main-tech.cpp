#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>
#include <fstream>


#include "algo.hpp"


/**
 * Generates tech data table from one source [0]
 * 
 * type t_dijkstra  t_dial
 */
void ss_tech(std::string location_path, std::string file_name,  std::string row_name, std::string result_path){
    // std::string full_path = graph_path;
    std::string graph_path = location_path + file_name;
    int s = 0;
    Graph* g = new Graph(graph_path);
    int t_dijkstra;
    int t_dial;

    auto start_time = std::chrono::high_resolution_clock::now();
    g->dijkstra(s);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
    t_dijkstra = time_diff.count(); // casting to miliseconds in int

    start_time = std::chrono::high_resolution_clock::now();
    g->dial(s);
    end_time = std::chrono::high_resolution_clock::now();
    time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
    t_dial = time_diff.count(); // casting to miliseconds in int


    std::ofstream file;
    file.open(result_path, std::ios_base::app);
    if(!file.is_open()){
        std::cout << "Error: Result file not open\n";
    }
    file << row_name << " " << t_dijkstra << " " << t_dial << std::endl;
    file.close();

}

void generate_R4_n(int range_start, int range_end){
    std::string result_path = "results/R4_n.txt"; // DEBUG
    std::string location_path = "DIMACS/ch9-1.1/inputs/Random4-n/";
    std::string base_name = "Random4-n.";
    std::string suffix = ".0.gr";

    for(int i=range_start; i<=range_end; i++){
        std::string index_string = std::to_string(i);
        std::string full_name = location_path;
        std::string file_name = base_name + index_string + suffix;
        std::cout << ">> [" << i << " / " << range_end << "]: "<< file_name <<"\t|";
        ss_tech(location_path, file_name, std::to_string(i), result_path);
        std::cout << " done\n";
    }
}



void generate_R4_C(int range_start, int range_end){
    std::string result_path = "results/R4_C.txt";
    std::string location_path = "DIMACS/ch9-1.1/inputs/Random4-C/";
    std::string base_name = "Random4-C.";
    std::string suffix = ".0.gr";
    // DIMACS/ch9-1.1/inputs/Random4-C/Random4-C.13.0.gr

    for(int i=range_start; i<=range_end; i++){
        std::string index_string = std::to_string(i);
        std::string full_name = location_path;
        std::string file_name = base_name + index_string + suffix;
        std::cout << ">> [" << i << " / " << range_end << "]: "<< file_name <<"\t|";
        ss_tech(location_path, file_name, std::to_string(i), result_path);
        std::cout << " done\n";
    }
}

// void generate_Square_n(int range){
//     std::string result_path = "results/Square_n.txt"
// }

// void generate_USA_road_t(){
//     std::string result_path = "results/USA_road_t.txt"
// }


int main(){
    // ss_tech("DIMACS/ch9-1.1/inputs/Random4-n/Random4-n.10.0.gr", "ss_tech_result.txt");
    generate_R4_n(10, 12);
    generate_R4_C(1, 2);

}