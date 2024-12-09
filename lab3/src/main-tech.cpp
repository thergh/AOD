#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>
#include <fstream>


#include "algo.hpp"

void print_vector(std::vector<int> v );

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


void generate(std::string test_name, int range_start, int range_end){
    std::string result_path = "results/" + test_name + ".txt";
    std::string location_path = "ch9-1.1/inputs/" + test_name + "/";
    std::string base_name = test_name + ".";
    std::string suffix = ".0.gr";
    
    for(int i=range_start; i<=range_end; i++){
        std::string index_string = std::to_string(i);
        std::string full_name = location_path;
        std::string file_name = base_name + index_string + suffix;
        std::cout << ">> [" << i << " / " << range_end << "]: "<< file_name <<"\t|";

        auto start_time = std::chrono::high_resolution_clock::now();

        ss_tech(location_path, file_name, std::to_string(i), result_path);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
        auto time = float(time_diff.count()) / 1000000; // casting to miliseconds in int

        std::cout << " completed, time: " << time << " sec" << std::endl;
    }
}

void generate_USA(std::string test_name){
    std::string result_path = "results/USA-road-d.txt";
    std::string location_path = "inputs/USA-road-d/";
    std::string prefix = "USA-road-d.";
    std::string suffix = ".gr";

    std::string file_name = prefix + test_name + suffix;
    std::cout << ">> " << file_name <<"\t|";

    auto start_time = std::chrono::high_resolution_clock::now();

    ss_tech(location_path, file_name, test_name, result_path);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
    auto time = float(time_diff.count()) / 1000000; // casting to miliseconds in int

    std::cout << " completed, time: " << time << " sec" << std::endl;
    
}

void generate_all_USA(){
    std::vector<std::string> names = {"BAY", "CAL", "COL", "FLA", "LKS", "NE", "NW", "NY"};
    for(const auto& n : names){
        generate_USA(n);
    }
    
}


void run_all(int start, int end){
    generate("Random4-n", start, end);
    generate("Random4-C", start, end);
    generate("Square-n", start, end);
    generate("Square-C", start, end);
    generate("Long-n", start, end);
    generate("Long-C", start, end);
}


void to_file(std::string output_path, int problem_size, int t_0_dijkstra, int t_0_dial,
            int t_avg_dijkstra, int t_avg_dial){

    std::ofstream ofs;
    ofs.open(output_path, std::ios_base::app);
    if(!ofs.is_open()){
        std::cout << "Error: Result file not open\n";
    }
    ofs << problem_size << " " << t_0_dijkstra << " " << t_0_dial  << " " << t_avg_dijkstra << " " << t_avg_dial<< std::endl;
    ofs.close();
}

/**
 * returns vector: {rozmiar, t-0-Dijkstra, t-0-dial, t-avg-Dijkstra, t-avg-dial}
 */
std::vector<int> run_algos(int size, std::string input_path){
    std::vector<int> results(5);

    Graph* g = new Graph(input_path);

    // t-0-Dijkstra
    auto start_time = std::chrono::high_resolution_clock::now();
    g->dijkstra(0);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
    int t_0_dijkstra = time_diff.count(); // casting to miliseconds in int

    // t-0-dial
    start_time = std::chrono::high_resolution_clock::now();
    g->dial(0);
    end_time = std::chrono::high_resolution_clock::now();
    time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
    int t_0_dial = time_diff.count(); // casting to miliseconds in int

    // t-avg-Dijkstra
    int t_avg_dijkstra = 0;


    // t-avg-dial
    int t_avg_dial = 0;

    results = {size, t_0_dijkstra, t_0_dial, t_avg_dijkstra, t_avg_dial};
    return results;
}

void to_file_big(){};

int main(){
    // run_all(10, 10);
    // generate_all_USA();
    // to_file("results/mock-to_file.txt", 1, 2, 3, 4, 5)
    std::string input_path = "ch9-1.1/inputs";
    auto v = run_algos(0, "ch9-1.1/inputs/Long-C/Long-C.0.0.gr");
    // print_vector(v);
    to_file("results/mock-to_file.txt", v[0], v[1], v[2], v[3], v[4]);
    
}