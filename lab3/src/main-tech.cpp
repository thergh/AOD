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


std::vector<int> comp_dist_rnd(std::string input_path, int iterations){
    Graph* g = new Graph(input_path);
    int end = g->V - 1;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distrib(0, end);

    long int dist_dijkstra_sum = 0;
    long int dist_dial_sum = 0;
    long int dist_radix_sum = 0;

    for(int i=0; i<iterations; i++){
        int v1 = distrib(rng);
        int v2 = distrib(rng);
        auto v_dijkstra = g->dijkstra(v1);
        auto v_dial = g->dial(v1);
        auto v_radix = g->radix(v1);
        dist_dijkstra_sum += v_dijkstra[v2];
        dist_dial_sum += v_dial[v2];
        dist_radix_sum += v_radix[v2];
    }

    int dist_dijkstra_avg = dist_dijkstra_sum / iterations;
    int dist_dial_avg = dist_dial_sum / iterations;
    int dist_radix_avg = dist_radix_sum / iterations;
    return {dist_dijkstra_avg, dist_dial_avg, dist_radix_avg};
}




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


std::vector<int> comp_time_rnd(std::string input_path, int iterations){
    Graph* g = new Graph(input_path);
    int end = g->V - 1;

    std::chrono::_V2::system_clock::time_point start_time;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distrib(0, end);

    long unsigned time_dijkstra_sum = 0;
    long unsigned time_dial_sum = 0;
    long unsigned time_radix_sum = 0;      

    for(int i=0; i<iterations; i++){
        int source = distrib(rng);
        
        start_time = std::chrono::high_resolution_clock::now();
        g->dijkstra(source);
        time_dijkstra_sum += time_diff(start_time);
    
        start_time = std::chrono::high_resolution_clock::now();
        g->dial(source);
        time_dial_sum += time_diff(start_time);

        start_time = std::chrono::high_resolution_clock::now();
        g->radix(source);
        time_radix_sum += time_diff(start_time);
    }  

    int time_dijkstra_avg = time_dijkstra_sum / iterations;
    int time_dial_avg = time_dial_sum / iterations;
    int time_radix_avg = time_radix_sum / iterations;
    return {time_dijkstra_avg, time_dial_avg, time_radix_avg};
}


void save_dist(std::string input_path, std::string name){
    std::string output_path = "results/dist-results.txt";
    int source = 0;
    auto dist_v = comp_dist(input_path, source);
    std::vector<std::string> v = {name, std::to_string(dist_v[0]), std::to_string(dist_v[1]), std::to_string(dist_v[2])};
    v_to_file(v, output_path);
}


void save_dist_rnd(std::string input_path, std::string name){
    std::string output_path = "results/dist-rnd-results.txt";
    int itr = 5;
    auto dist_v = comp_dist_rnd(input_path, itr);
    std::vector<std::string> v = {name, std::to_string(dist_v[0]), std::to_string(dist_v[1]), std::to_string(dist_v[2])};
    v_to_file(v, output_path);
}


void save_time(std::string input_path, std::string name, int size){
    std::string output_path = "results/" + name + ".txt";
    int source = 0;
    auto dist_v = comp_time(input_path, source);
    std::vector<std::string> v = {std::to_string(size), std::to_string(dist_v[0]),
                                std::to_string(dist_v[1]), std::to_string(dist_v[2])};
    v_to_file(v, output_path);
}


void save_time_avg(std::string input_path, std::string name, int size){
    std::string output_path = "results/" + name + "-rnd" + ".txt";
    int itr = 5;
    auto dist_v = comp_time_rnd(input_path, itr);
    std::vector<std::string> v = {std::to_string(size), std::to_string(dist_v[0]),
                                std::to_string(dist_v[1]), std::to_string(dist_v[2])};
    v_to_file(v, output_path);
}


void run_time(std::string name, int start_idx, int end_idx){
    std::string dir_path = "ch9-1.1/inputs/" + name + "/";
    std::string suffix = ".0.gr";

    for(int i=start_idx; i<=end_idx; i++){
        auto start_time = std::chrono::high_resolution_clock::now();
        std::string input_path = dir_path + name + "." + std::to_string(i) + suffix;
        save_time(input_path, name, i);
        auto time = time_diff(start_time);
        std::cout << input_path << "; time: " << time / 1000000 << " sec" << std::endl;
    }
}


void run_time_avg(std::string name, int start_idx, int end_idx){
    std::string dir_path = "ch9-1.1/inputs/" + name + "/";
    std::string suffix = ".0.gr";

    for(int i=start_idx; i<=end_idx; i++){
        auto start_time = std::chrono::high_resolution_clock::now();
        std::string input_path = dir_path + name + "." + std::to_string(i) + suffix;
        save_time_avg(input_path, name, i);
        auto time = time_diff(start_time);
        std::cout << input_path << "; time: " << time / 1000000 << " sec" << std::endl;
    }
}


void run_all_n(int start_idx, int end_idx){
    run_time("Long-n", start_idx, end_idx);
    run_time("Square-n", start_idx, end_idx);
    run_time("Random4-n", start_idx, end_idx);
    run_time_avg("Long-n", start_idx, end_idx);
    run_time_avg("Square-n", start_idx, end_idx);
    run_time_avg("Random4-n", start_idx, end_idx);
}


void run_all_C(int start_idx, int end_idx){
    // run_time("Long-C", start_idx, end_idx);
    // run_time("Square-C", start_idx, end_idx);
    // run_time("Random4-C", start_idx, end_idx);
    // run_time_avg("Long-C", start_idx, end_idx);
    // run_time_avg("Square-C", start_idx, end_idx);
    // run_time_avg("Random4-C", start_idx, end_idx);
}


int main(){
    // run_all_C(4, 8);
    // run_all_n(10, 18);
    run_time("Long-C", 1, 1);
}