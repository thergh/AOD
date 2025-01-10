#include <iostream>
#include <fstream>

#include "algo.hpp"


int main(int argc, char* argv[]){
    std::string prefix = "output/bip-time-";
    std::string suffix = ".out";
    int start_k = 3;
    int end_k = 10; 
    int i = 9;
    int reps = 5;
    std::string output_path = prefix + std::to_string(i) + suffix;
    
    std::cout << "TESTING BIPARTITE TIME; " << "i: " << i  << "; reps: " << reps << std::endl;

    for(int x=start_k; x<=end_k; x++){
        std::cout << x << "/" << end_k << "\t| ";

        size_t max_flow_sum = 0;
        size_t time_sum = 0;
        size_t paths_sum = 0;

        for(int j=0; j<reps; j++){
            Graph* cube = new Graph();
            cube->gen_bipartite(x, i);
            max_flow_sum + cube->max_flow();
            time_sum += cube->alg_time;
        }
        std::ofstream outfile;
        outfile.open(output_path, std::ios_base::app);
        outfile << x << " " << time_sum/reps << std::endl;

        std::cout << time_sum / 1000 << " sec" << std::endl;
    }
}