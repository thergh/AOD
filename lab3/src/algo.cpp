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


#include "algo.hpp"


Graph::Graph(std::string input_path){
    std::ifstream input(input_path);
    std::string line;

    this->max_weight = 0;

    // // DEBUG
    // this->adjacency_list = std::vector<std::vector<std::pair<int, int>>>(10);
    
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
            this->adjacency_list = std::vector<std::vector<std::pair<int, int>>>(this->V);       
        }
        else if(line[0] == 'a'){
            std::vector<std::string> words;
            std::string word;
            std::istringstream ss(line);
            while(ss >> word){
                words.push_back(word);
            }
            // decerasing by one to make vertices start from 0 instead of 1, to match vector convention

            add_edge(stoul(words[1]) - 1, stoul(words[2]) - 1, stoul(words[3]));

            // calculating max weight
            if(stoi(words[3]) > this->max_weight){
                this->max_weight = stoi(words[3]);
            }
        }
        
    }

}



Graph::Graph(int V){
    this->V = V;
    this->adjacency_list = std::vector<std::vector<std::pair<int, int>>>(V);
}


void Graph::add_edge(int a, int b, int weight){
    this->adjacency_list[a].push_back(std::make_pair(b, weight));
}


void Graph::print_graph(){
    // increasing by one to make vertices start from1 instead of 0,
    // to match vector convention
    for(int i=0; i<int(this->adjacency_list.size()); i++){
        std::cout << i + 1 << ":\t";
        for(int j=0; j<int(this->adjacency_list[i].size()); j++){
            std::cout << "(" << adjacency_list[i][j].first + 1 << ", " << adjacency_list[i][j].second<< "), ";
        }
        std::cout << "\n";
    }
}


std::vector<int> Graph::ss_from_file(std::string ss_path){
    std::vector<int> ss_vector;
    std::ifstream input(ss_path);
    std::string line;

    while(std::getline(input, line)){
        
        if(line[0] == 's'){
            std::cout << line << "\n";
            std::vector<std::string> words;
            std::string word;
            std::istringstream ss(line);
            while(ss >> word){
                words.push_back(word);
            }
            ss_vector.push_back(stoul(words[1]));
        }
    }   
    return ss_vector;
}


std::vector<std::pair<int, int>> Graph::p2p_from_file(std::string p2p_path){
    std::vector<std::pair<int, int>> p2p_vector(0);
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
            p2p_vector.push_back(std::make_pair(stoul(words[1]), stoul(words[2])));
        }
    }   
    return p2p_vector;    
}


void Graph::ss_result(int V, int E, std::pair<int, int> range, float avg_time,
                    std::string data_path, std::string ss_path, std::string result_path){
    std::ofstream file;
    file.open(result_path);
    file << "c wyniki dla danych:\n";
    file << "f " << data_path << " " << ss_path << std::endl;
    file << "c\n";
    file << "c V\tE\tmin\tmax\n";
    file << "g " << V << "\t" << E << "\t" << range.first << "\t" << range.second << "\t" << std::endl;
    file << "c\n";
    file << "c sredni czas wykonania:\n";
    file << "t " << avg_time << std::endl;
    file.close();
}


void Graph::p2p_result(int V, int E, std::vector<std::tuple<int, int, int>> dists,
                    std::pair<int, int> range, float avg_time,
                    std::string data_path, std::string p2p_path, std::string result_path){
    std::ofstream file;
    file.open(result_path);
    file << "c wyniki dla danych:\n";
    file << "f " << data_path << " " << p2p_path << std::endl;
    file << "c\n";
    file << "c V\tE\tmin\tmax\n";
    file << "g " << V << "\t" << E << "\t" << range.first << "\t" << range.second << "\t" << std::endl;
    file << "c\n";
    file << "c dlugosc najkrotszych sciezek:\n";
    file << "c u\tv\tdlugosc\n";
    for(const auto& d : dists){
        file << "d " << std::get<0>(d) << "\t"<< std::get<1>(d) << "\t"<< std::get<2>(d) << "\n";
    }
    file << "c\n";
    file << "c sredni czas wykonania:\n";
    file << "t " << avg_time << std::endl;
    file.close();
}


std::vector<int> Graph::dijkstra(int source){
    // algorithm implemented following Cormen's pseudocode
    class Node{
    public:
        int index; // index in adj. tree
        int current_d; // current shortest distance

        void print_node(){
            std::cout << "(" << index << ", " << current_d << ")" << "\n";
        }

        Node(int index, int current_d){
            this->index = index;
            this->current_d = current_d;
        }

        // overloading < to use in min heap (priority queue)
        bool operator<(const Node& other_node) const{
            // using ">" to create a min heap
            return current_d > other_node.current_d;
        }
    };

    int size = this->adjacency_list.size(); // vertex count
    int max_int = std::numeric_limits<int>::max();
    std::priority_queue<Node> Q; // min heap based priority queue
    std::vector<int> distances(size, max_int); // shortest known distances to vertices

    // initializing Q and distances from adj. list
    for(int i=0; i<size; i++){
        // initializing current distance as max_int
        Node new_node = Node(i, max_int);
        distances[i] = max_int;
        // new_node.print_node();
        Q.push(new_node);
    }

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
            int v_index = v.first;
            int v_weight = v.second;

            // updating distance and adding new node to Q if it's shorter
            if(distances[u.index] + v_weight < distances[v_index]){
                distances[v_index] = distances[u.index] + v_weight;
                Q.push(Node(v_index, distances[v_index]));
            }
        }
    }

    return distances;
}


std::vector<int> Graph::dial(int source){

    int size = this->adjacency_list.size();
    const int MAX_INT = std::numeric_limits<int>::max();
    const int MAX_DIST = this->max_weight;

    // iterator to have access to elements in old buckets
    std::vector<int> dist(size, std::numeric_limits<int>::max());
    std::vector<std::list<int>> buckets(MAX_DIST + 1);

    dist[source] = 0;
    buckets[0].push_back(source);

    int bucket_index = 0;

    while(bucket_index <= MAX_DIST){
        
        // lookign for the first non-empty bucket
        while(bucket_index <= MAX_DIST && buckets[bucket_index].empty()){
            bucket_index++;
        }

        if(bucket_index > MAX_DIST){
            break;
        }

        // iterate over all nodes in the current bucket
        while(!buckets[bucket_index].empty()){
            int u = buckets[bucket_index].front();
            buckets[bucket_index].pop_front();

            // iterate over adjacent nodes
            for(const auto& edge : adjacency_list[u]){
                int v = edge.first;
                int v_dist = edge.second;

                // update distance
                if(dist[u] + v_dist < dist[v]){
                    if(dist[v] != MAX_INT){
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




void find_nonempty(){
    return;
}


void redistribute(){

}


bool in_range(int x, std::pair<int, int> p){
    return (x >= p.first && x <= p.second);
}


std::vector<int> Graph::radixheap(int source){
    const int SIZE = this->adjacency_list.size();
    const int MAX_INT = std::numeric_limits<int>::max();
    const int MAX_DIST = this->max_weight;
    const int K = SIZE * MAX_DIST;
    const int BUCKET_NUMBER = log2(K); // maybe add 1?

    std::vector<int> dist(SIZE);
    std::vector<std::list<int>> buckets(BUCKET_NUMBER); // maybe MAX_DIST + 1??
    std::vector<std::pair<int, int>> ranges(BUCKET_NUMBER);
    std::cout << "MAX_DIST: " << MAX_DIST << "\n";
    std::cout << "bucket size: " << buckets.size() << "\n";

    dist[source] = 0;
    // buckets[0].push_back(source);

    // init ranges
    ranges[0] = {1, 1};
    for(int i=1; i<BUCKET_NUMBER; i++){
        ranges[i] = {std::pow(2, i - 1), std::pow(2, i) - 1};
    }

    // for(auto r : ranges){ // printing bucket ranges
    //     std::cout << "(" << r.first << ", " << r.second << ")\n";
    // }
    // std::cout << in_range(20, ranges.back());

    // while(true){ // we escape if last bucket is empty


    // }
    return dist;

}