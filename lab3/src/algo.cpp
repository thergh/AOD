#include <iostream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <limits>
#include <list>
#include <cmath>
#include <algorithm>
#include <functional>
#include <utility>
#include <cassert>


#include "algo.hpp"


Graph::Graph(std::string input_path){
    std::ifstream input(input_path);
    if(input.is_open()){
        
    }
    else{
        std::cout << "Error: Input file not open\n";
    }
    std::string line;

    this->max_weight = 0;

    // // DEBUG
    // this->adjacency_list = std::vector<std::vector<std::pair<size_t, size_t>>>(10);
    
    while(std::getline(input, line)){
        // std::cout << line << "\n";

        if(line[0] == 'c'){
            continue;
        }
        else if(line[0] == 'p'){
            std::vector<std::string> words;
            std::string word;
            std::istringstream ss(line);
            while(ss >> word){
                words.push_back(word);
            }
            this->V = stoul(words[2]);
            // std::cout << "V: " << words[2] << "\n";
            this->E = stoul(words[3]);
            // std::cout << "E: " << E << "\n";
            this->adjacency_list = std::vector<std::vector<std::pair<size_t, size_t>>>(this->V);       
        }
        else if(line[0] == 'a'){
            std::vector<std::string> words;
            std::string word;
            std::istringstream ss(line);
            while(ss >> word){
                words.push_back(word);
            }
            // decerasing by one to make vertices start from 0 instead of 1,
            // to match vector convention

            add_edge(stoul(words[1]) - 1, stoul(words[2]) - 1, stoul(words[3]));

            // calculating max weight
            if(static_cast<size_t>(std::stol(words[3])) > this->max_weight){
                this->max_weight = static_cast<size_t>(std::stol(words[3]));
            }
        }
        
    }

}



Graph::Graph(size_t V){
    this->V = V;
    this->adjacency_list = std::vector<std::vector<std::pair<size_t, size_t>>>(V);
}


void Graph::add_edge(size_t a, size_t b, size_t weight){
    this->adjacency_list[a].push_back(std::make_pair(b, weight));
}


void Graph::prsize_t_graph(){
    // increasing by one to make vertices start from1 instead of 0,
    // to match vector convention
    for(size_t i=0; i<size_t(this->adjacency_list.size()); i++){
        std::cout << i + 1 << ":\t";
        for(size_t j=0; j<size_t(this->adjacency_list[i].size()); j++){
            std::cout << "(" << adjacency_list[i][j].first + 1 << ", " << adjacency_list[i][j].second<< "), ";
        }
        std::cout << "\n";
    }
}


std::vector<size_t> Graph::ss_from_file(std::string ss_path){
    std::vector<size_t> ss_vector;
    std::ifstream input(ss_path);
    std::string line;

    while(std::getline(input, line)){
        
        if(line[0] == 's'){
            // std::cout << line << "\n";
            std::vector<std::string> words;
            std::string word;
            std::istringstream ss(line);
            while(ss >> word){
                words.push_back(word);
            }
            ss_vector.push_back(stoul(words[1]) - 1);
        }
    }   
    return ss_vector;
}


std::vector<std::pair<size_t, size_t>> Graph::p2p_from_file(std::string p2p_path){
    std::vector<std::pair<size_t, size_t>> p2p_vector(0);
    std::ifstream input(p2p_path);
    std::string line;

    while(std::getline(input, line)){
        if(line[0] == 'q'){
            // std::cout << line << "\n";
            std::vector<std::string> words;
            std::string word;
            std::istringstream ss(line);

            while(ss >> word){
                words.push_back(word);
            }
            p2p_vector.push_back(std::make_pair(stoul(words[1]) - 1, stoul(words[2]) - 1));
        }
    }   
    return p2p_vector;    
}


void Graph::ss_result(size_t V, size_t E, std::pair<size_t, size_t> range, size_t avg_time,
                    std::string data_path, std::string ss_path, std::string result_path){
    std::ofstream file;
    file.open(result_path);
    file << "c wyniki dla danych:\n";
    file << "f " << data_path << " " << ss_path << std::endl;
    file << "c wierzchołki: " << V <<", krawędzie: " << E << ", zakres długości: [" << range.first << ", " << range.second << "]\n";
    file << "g " << V << " " << E << " " << range.first << " " << range.second << " " << std::endl;
    file << "c\n";
    file << "c sredni czas wykonania: " << avg_time <<"\n";
    file << "t " << avg_time << std::endl;
    file.close();
}


void Graph::p2p_result(size_t V, size_t E, std::vector<std::tuple<size_t, size_t, size_t>> dists,
                    std::pair<size_t, size_t> range, size_t avg_time,
                    std::string data_path, std::string p2p_path, std::string result_path){
    std::ofstream file;
    file.open(result_path);
    file << "c wyniki dla danych:\n";
    file << "f " << data_path << " " << p2p_path << std::endl;
    file << "c\n";
    file << "c wierzchołki: " << V <<", krawędzie: " << E << ", zakres długości krawędzi: [" << range.first << ", " << range.second << "]\n";
    file << "g " << V << " " << E << " " << range.first << " " << range.second << " " << std::endl;
    file << "c\n";
    file << "c dlugosc najkrotszych sciezek:\n";
    file << "c u\tv\tdist(u, v)\n";
    for(const auto& d : dists){
        file << "d " << std::get<0>(d) + 1 << " "<< std::get<1>(d) + 1 << " "<< std::get<2>(d) << "\n";
    }
    file << "c\n";
    file << "c sredni czas wykonania:\n";
    file << "t " << avg_time << std::endl;
    file.close();
}


std::vector<size_t> Graph::dijkstra(size_t source){
    // algorithm implemented following Cormen's pseudocode
    class Node{
    public:
        size_t index; // index in adj. tree
        size_t current_d; // current shortest distance

        void prsize_t_node(){
            std::cout << "(" << index << ", " << current_d << ")" << "\n";
        }

        Node(size_t index, size_t current_d){
            this->index = index;
            this->current_d = current_d;
        }

        // overloading < to use in min heap (priority queue)
        bool operator<(const Node& other_node) const{
            // using ">" to create a min heap
            return current_d > other_node.current_d;
        }
    };

    size_t size = this->adjacency_list.size(); // vertex count
    size_t max_size_t = std::numeric_limits<size_t>::max();
    std::priority_queue<Node> Q; // min heap based priority queue
    std::vector<size_t> distances(size, max_size_t); // shortest known distances to vertices

    // push the source node with distance 0
    distances[source] = 0;
    Q.push(Node(source, 0));

    while(!Q.empty()){
        Node u = Q.top();
        Q.pop();

        // ignoring stale nodes that are created because instead
        // of implementing decrease_key() we apply the "Lazy Update" technique
        // that leaves redundant nodes in the queue
        if(u.current_d > distances[u.index]){
            continue;
        }

        for(const auto& v : adjacency_list[u.index]){
            size_t v_index = v.first;
            size_t v_weight = v.second;

            // updating distance and adding new node to Q if it's shorter
            if(distances[u.index] + v_weight < distances[v_index]){
                distances[v_index] = distances[u.index] + v_weight;
                Q.push(Node(v_index, distances[v_index]));
            }
        }
    }

    return distances;
}


std::vector<size_t> Graph::dial(size_t source){
    size_t size = this->adjacency_list.size();
    const size_t MAX_size_t = std::numeric_limits<size_t>::max();
    const size_t MAX_DIST = this->max_weight;
    size_t nodes_processed = size;
    std::vector<size_t> dist(size, std::numeric_limits<size_t>::max());
    std::vector<std::list<size_t>> buckets(MAX_DIST + 1);

    dist[source] = 0;
    buckets[0].push_back(source);

    size_t bucket_index = 0;
    while(nodes_processed > 0){
        while(buckets[bucket_index].empty()){
            bucket_index = (bucket_index + 1) % (MAX_DIST + 1);  
        }

        // iterate over all nodes in the current bucket
        while(!buckets[bucket_index].empty()){
            size_t u = buckets[bucket_index].front();
            buckets[bucket_index].pop_front();
            nodes_processed --;

            // iterate over adjacent nodes
            for(const auto& edge : adjacency_list[u]){
                size_t v = edge.first;
                size_t v_dist = edge.second;

                // update distance
                if(dist[u] + v_dist < dist[v]){
                    if(dist[v] != MAX_size_t){
                        buckets[dist[v] % (MAX_DIST + 1)].remove(v);
                    }
                    dist[v] = dist[u] + v_dist;
                    buckets[dist[v] % (MAX_DIST + 1)].push_back(v);
                }
            }
        }
    }
    return dist;
}


Radix_Heap::Radix_Heap(size_t max_dist){
    this->size = static_cast<size_t>(std::log2(max_dist)) + 2;
    this->current_min = 0;
    buckets.resize(size);
    ranges.resize(size);

    // init ranges
    ranges[0] = {0, 0};
    for(size_t i=1; i<size-1; i++){
        ranges[i] = {static_cast<size_t>(std::pow(2, i - 1)), static_cast<size_t>(std::pow(2, i)) - 1};
    }
    ranges[size - 1] = {static_cast<size_t>(std::pow(2, size - 2)), INT64_MAX};
}


void Radix_Heap::insert(size_t vertex, size_t dist){
    size_t bucket_index = get_bucket_index(dist);
    buckets[bucket_index].push_back({vertex, dist});
}


std::pair<size_t, size_t> Radix_Heap::extract_first(){
    // finding the first non-empty bucket
    for(size_t i=0; i<size; i++){
        if(!buckets[i].empty()){

            // using iter. to calc current_min based on this bucket's min
            auto it = std::min_element(
                buckets[i].begin(),
                buckets[i].end(),
                [](const node& a, const node& b){return a.dist < b.dist;}
            );

            current_min = it->dist;
            size_t vertex = it->vertex;
            buckets[i].erase(it);

            // redistributing remaining items if necessary
            if(buckets[i].empty() && i>0){
                for(const auto& n : buckets[i]){
                    size_t new_bucket = get_bucket_index(n.dist);
                    buckets[new_bucket].push_back(n);
                }
                buckets[i].clear();
            }

            return {vertex, current_min};
        }
    }
    // in this case the heap is already empty
    throw std::runtime_error("Error: Heap is empty");
}


size_t Radix_Heap::get_bucket_index(size_t dist) const {
    for(size_t i = 0; i < size; i++){
        if(dist >= ranges[i].first && dist <= ranges[i].second){
            return i;
        }
    }
    return size - 1; // edge case for max distance
}


bool Radix_Heap::empty() const {
    for(const auto& bucket : buckets){
        if(!bucket.empty()){
            return false;
        }
    }
    return true;
}


std::vector<size_t> Graph::radix(size_t source){
    const size_t SIZE = this->adjacency_list.size(); // vertex count
    const size_t C = this->max_weight;

    Radix_Heap heap(C);
    std::vector<size_t> distances(SIZE, INT64_MAX);
    std::vector<bool> visited(SIZE, false);

    // push the source node with distance 0
    heap.insert(source, 0);
    distances[source] = 0;

    while(!heap.empty()){
        auto u = heap.extract_first();

        if(visited[u.first]){
            continue;
        }

        visited[u.first] = true;

        for(const auto& v : adjacency_list[u.first]){
            size_t v_index = v.first;
            size_t v_weight = v.second;
            size_t new_dist = distances[u.first] + v_weight;

            // updating distance
            if(new_dist < distances[v_index]){
                distances[v_index] = new_dist;
                heap.insert(v_index, distances[v_index]);
            }
        }
    }
    return distances;
}







