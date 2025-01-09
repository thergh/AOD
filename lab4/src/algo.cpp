#include <iostream>
#include <bitset>
#include <algorithm>


#include "algo.hpp"


Hypercube::Hypercube(int k) : k(k){
    int n = 1 << k;
    srand (time(NULL));
    
    this->adj_list.resize(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            int neighbour = i ^ (1 << j);
            if(neighbour > i){
                this->adj_list[i].push_back(neighbour);
                int h_i = __builtin_popcount(i);
                int z_i = k - h_i;
                int h_j = __builtin_popcount(neighbour);
                int z_j = k - h_j;
                int l = std::max({h_i, z_i, h_j, z_j});
                int capacity = rand() % (1 << l) + 1;
                std::cout << capacity << std::endl;
                this->capacities[{i, neighbour}] = capacity; 
            }
        }
    }
}


void Hypercube::display_adj(){
    for(int i=0; i<this->adj_list.size(); i++){
        std::cout << std::bitset<4>(i) << ": [ ";
        for(int j=0; j<this->adj_list[i].size(); j++){
            std::cout << std::bitset<4>(this->adj_list[i][j]) << " ";
        }
        std::cout << "]\n";
    }
}


