#include <iostream>
#include <bitset>
#include <algorithm>
#include <queue>


#include "algo.hpp"


Hypercube::Hypercube(int k) : k(k){
    int n = 1 << k;
    this->n = n;

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
                this->capacities[{i, neighbour}] = capacity; 
            }
        }
    }
}


void Hypercube::display_adj(){
    for(int i=0; i<this->adj_list.size(); i++){
        std::cout << std::bitset<4>(i) << ": [ ";
        for(int j=0; j<this->adj_list[i].size(); j++){
        }
        std::cout << "]\n";
    }
}


int Hypercube::max_flow(){
    int total_flow = 0;
    int source = 0;
    int sink = this->n - 1;
    std::map<std::pair<int, int>, int> flows;
    
    // BFS
    std::vector<int> parents(this->adj_list.size(), -1);
    std::queue<int> q;
    q.push(source);
    parents[source] = source;

    while(!q.empty() && parents[sink] == -1){
        int curr = q.front();
        q.pop();

        for(int neighb : this->adj_list[curr]){
            int residual = this->capacities[{curr, neighb}] - flows[{curr, neighb}];
            if(residual > 0 && parents[neighb] == -1){
                parents[neighb] = curr;
                q.push(neighb);
                if(neighb == sink){
                    break;
                }
            }
        }
    }


    return 1;
}



