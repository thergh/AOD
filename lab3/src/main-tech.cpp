#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>
#include <fstream>
#include <random>

#include "algo.hpp"

void print_vector(std::vector<int> v );


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
std::vector<int> compare_algos(int size, std::string input_path){
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
    
    // rng
    int V = g->V;
    std::random_device r_dev;
    std::mt19937 rng(r_dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, V - 1); // distribution in range [1, 6]

    int t_sum_dijkstra = 0;
    std::vector<int> times_dijkstra;
    int t_sum_dial = 0;
    std::vector<int> times_dial; 

    for(int i=0; i<4; i++){
        int random_idx = dist(rng);

        // random index dijkstra
        start_time = std::chrono::high_resolution_clock::now();
        g->dijkstra(random_idx);
        end_time = std::chrono::high_resolution_clock::now();
        time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
        int t_rnd_dijkstra = time_diff.count(); // casting to miliseconds in int
        times_dijkstra.push_back(t_rnd_dijkstra);
        t_sum_dijkstra += t_rnd_dijkstra;

        // random index dial
        start_time = std::chrono::high_resolution_clock::now();
        g->dial(random_idx);
        end_time = std::chrono::high_resolution_clock::now();
        time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
        int t_rnd_dial = time_diff.count(); // casting to miliseconds in int
        times_dial.push_back(t_rnd_dial);
        t_sum_dial += t_rnd_dial;
    }   

    int t_avg_dijkstra = t_sum_dijkstra / 4;
    int t_avg_dial = t_sum_dial / 4;

    results = {size, t_0_dijkstra, t_0_dial, t_avg_dijkstra, t_avg_dial};
    return results;
}


void run_test_file(std::string test_name, int start_idx, int end_idx){
    std::string output_path = "results/" + test_name + ".txt";
    std::string location_path = "ch9-1.1/inputs/" + test_name + "/";
    std::string base_name = test_name + ".";
    std::string suffix = ".0.gr";

    for(int i=start_idx; i<=end_idx; i++){
        auto start_time = std::chrono::high_resolution_clock::now();

        std::cout << ">> [" << i << " / " << end_idx << "]: "<< test_name <<"\t|";

        std::string index_string = std::to_string(i);
        std::string full_name = base_name + index_string + suffix;
        std::string test_path = location_path + full_name;

        auto v = compare_algos(i, test_path);
        to_file(output_path, v[0], v[1], v[2], v[3], v[4]);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto time_diff = duration_cast<std::chrono::microseconds>(end_time - start_time);
        int time = time_diff.count() / 1000000; // casting to miliseconds in int

        std::cout << " completed, time : " << time << " sec" << std::endl;
    }
}


void run_C_tests(int start_idx, int end_idx){
    run_test_file("Long-C", start_idx, end_idx);
    run_test_file("Random4-C", start_idx, end_idx);
    run_test_file("Square-C", start_idx, end_idx);
};

void run_n_tests(int start_idx, int end_idx){
    run_test_file("Long-n", start_idx, end_idx);
    run_test_file("Random4-n", start_idx, end_idx);
    run_test_file("Square-n", start_idx, end_idx);
};


void to_file_dist(std::string output_path, int index, int d_0_dijkstra, int d_0_dial,
            int d_avg_dijkstra, int d_avg_dial, int t_avg_dijkstra, int t_avg_dial){

    std::ofstream ofs;
    ofs.open(output_path, std::ios_base::app);
    if(!ofs.is_open()){
        std::cout << "Error: Result file not open\n";
    }
    ofs << index << " " << d_0_dijkstra << " " << d_0_dial  << " " << d_avg_dijkstra  << " " <<  d_avg_dial  << " " <<  t_avg_dijkstra << " " << t_avg_dial<< std::endl;
    ofs.close();
}


/**
 * returns vector: {rozmiar, t-0-Dijkstra, t-0-dial, t-avg-Dijkstra, t-avg-dial}
 */
std::vector<int> compare_algos_dist(int index, std::string input_path){
    std::vector<int> results(5);
    Graph* g = new Graph(input_path);
    int V = g->V;

    // t-0-Dijkstra
    auto v_dijkstra = g->dijkstra(0);
    int d_0_dijkstra = v_dijkstra[V-1];
    // print_vector(v_dijkstra);
    // t-0-dial
    auto v_dial = g->dial(0);
    int d_0_dial = v_dial[V-1];
    // print_vector(v_dial);
    
    std::random_device r_dev;
    std::mt19937 rng(r_dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, V - 1); // distribution in range [1, 6]

    int d_sum_dijkstra = 0;
    std::vector<int> dist_dijkstra;
    int d_sum_dial = 0;
    std::vector<int> dist_dial; 

    for(int i=0; i<4; i++){
        int random_idx_1 = dist(rng);
        int random_idx_2 = dist(rng);

        // random index dijkstra
        auto v_a = g->dijkstra(random_idx_1);
        // print_vector(v_a);
        d_sum_dijkstra += v_a[random_idx_2];
        // random index dial
        auto v_b = g->dial(random_idx_1);
        // print_vector(v_b);
        d_sum_dial += v_b[random_idx_2];
    }   

    int d_avg_dijkstra = d_sum_dijkstra / 4;
    int d_avg_dial = d_sum_dial / 4;

    results = {index, d_0_dijkstra, d_0_dial, d_avg_dijkstra, d_avg_dial};
    // std::cout << "<><>ra: " << v_dijkstra[2];
    // std::cout << "<><>al: " << v_dial[2];
    return results;
}


int main(){
    // run_C_tests(1, 14);
    run_n_tests(10, 21);
    // to_file_dist("results/res-a.txt", 0, 1, 2, 3, 4, 5, 6);
    // print_vector(compare_algos_dist(1, "ch9-1.1/docs/format/samples/sample-c.gr.txt"));
    // print_vector(compare_algos_dist(1, "ch9-1.1/inputs/Square-n/Square-n.10.0.gr"));
    // compare_algos_dist(1, "ch9-1.1/inputs/Square-n/Square-n.10.0.gr");

}