#include <iostream>
#include <bitset>
#include <algorithm>
#include <queue>
#include <limits>
#include <random>
#include <chrono>
#include <set>


#include "algo.hpp"


Graph::Graph(){
}


void Graph::gen_hypercube(int k){
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
                this->capacities[{i, neighbour}] = capacity; 
            }
        }
    }
}


void Graph::gen_bipartite(int k, int i){
    int n = 1 << k;
    this->adj_list.resize(2 * n + 2);

    int source = 0;
    int sink = n * 2 + 1;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, n);

        for(int u=1; u<=n; u++){
        this->adj_list[source].push_back(u);
        this->adj_list[u].push_back(source);
        this->capacities[{source, u}] = 1;

        std::set<int> neighb;
        while(neighb.size() < i && neighb.size()<n){
            int v = dist(rng);
            neighb.insert(v);
        }
        for(int v : neighb){
            this->adj_list[u].push_back(v + n);
            this->adj_list[v + n].push_back(u);
            this->capacities[{u, v + n}] = 1;
        }
    }

    for(int v=1; v<=n; ++v){
        this->adj_list[v + n].push_back(sink);
        this->adj_list[sink].push_back(v + n);
        capacities[{v + n, sink}] = 1;
    }
}


void Graph::display_adj(){
    for(int i=0; i<this->adj_list.size(); i++){
        // std::cout << std::bitset<4>(i) << ": [ ";
        std::cout << i << ": [ ";
        for(int j=0; j<this->adj_list[i].size(); j++){
            std::cout << this->adj_list[i][j] << " ";
        }
        std::cout << "]\n";
    }
}


int Graph::max_flow(){
    int total_flow = 0;
    int source = 0;
    int sink = this->adj_list.size() - 1;
    std::map<std::pair<int, int>, int> flows;

    this->alg_time = 0;
    this->path_count = 0;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while(true){
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

        if(parents[sink] == -1){
            break;
        }

        // find bottleneck flow
        int bottleneck = std::numeric_limits<int>::max();
        int v = sink;
        while(v != source){
            int u = parents[v];
            bottleneck = std::min(bottleneck, capacities[{u, v}] - flows[{u, v}]);
            v = parents[v];
        }

        // update flow
        v = sink;
        while(v != source){
            int u = parents[v];
            flows[{u, v}] += bottleneck;
            flows[{v, u}] -= bottleneck;
            v = parents[v];
        }

        total_flow += bottleneck;
        this->path_count ++;

    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto time_diff_ms = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
    this->alg_time = time_diff_ms;
    this->final_flow = flows;

    return total_flow;
}


void Graph::display_flow(){
    for(auto& x : this->final_flow){
        std::cout << "(" << x.first.first << ", " << x.first.second << "): " << x.second << std::endl;
    }
}

