#include <iostream>
#include <fstream>

#include "algo.hpp"


int main(int argc, char* argv[]){
    std::string output_path = "output/hyp.out";
    int start_k = 15;
    int end_k = 16; 
    int reps = 2;
    
    std::cout << "TESTING HYPERCUBE; " << "reps: " << reps << std::endl;

    for(int x=start_k; x<=end_k; x++){
        std::cout << x << "/" << end_k << "\t| ";

        size_t max_flow_sum = 0;
        size_t time_sum = 0;
        size_t paths_sum = 0;

        for(int j=0; j<reps; j++){
            Graph* cube = new Graph();
            cube->gen_hypercube(x);
            max_flow_sum += cube->max_flow();
            time_sum += cube->alg_time;
            paths_sum += cube->path_count;
        }
        std::ofstream outfile;
        outfile.open(output_path, std::ios_base::app);
        outfile << x << " " << max_flow_sum/reps << " " << time_sum/reps << " " << paths_sum/reps << std::endl;

        std::cout << time_sum / 1000 << " sec" << std::endl;
    }
}