#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <limits>

#include "algo.hpp"


Graph::Graph(std::string input_path){
    std::ifstream input(input_path);
    std::string line;

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
    std::vector<int> ss_vector(0);
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


std::vector<int> Graph::dijkstra(int source){
    class node{
    public:
        int index; // index in adj. tree
        int current_d; // current shortest distance
        int final_d; // final shortest distance

        void print_node(){
            std::cout << "(" << index << ", " << current_d << ", " << final_d << ")" << "\n";
        }

        node(int index, int current_d, int final_d){
            this->index = index;
            this->current_d = current_d;
            this->final_d = final_d;
        }

        // overloading < to use in min heap (priority queue)
        bool operator<(const node& other_node) const{
            // using ">" to create a min heap
            return current_d > other_node.current_d;
        }
    };

    // vector of vertices with final distances
    // empty at the beggining
    std::vector<int> S;

    // for each node it must know:
    // its index
    // its current shortest distance
    // its final shortest distance??
    std::priority_queue<node> Q;

    // initializing Q from adj. list
    for(int i=0; i<int(this->adjacency_list.size()); i++){
        // setting current 
        int max_int = std::numeric_limits<int>::max();
        // initializing distance as max_int
        node new_node = node(i, max_int - i, max_int);
        new_node.print_node();
        Q.push(new_node);
    }
    // std::cout << "min node: " << Q.top().index << std::endl;

    // TODO: DEBUG!!! TEMP!!!
    return S;
}


// std::vector<int> Graph::dial(int source){}


// std::vector<int> Graph::radixheap(int source){}