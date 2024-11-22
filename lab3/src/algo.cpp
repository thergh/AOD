#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "algo.hpp"


Graph::Graph(std::string input_path){
    std::ifstream input(input_path);
    std::string line;

    // DEBUG
    this->adjacency_list = std::vector<std::vector<std::pair<size_t, int>>>(10);
    
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
            std::cout << "V: " << words[2] << "\n";
            this->E = stoul(words[3]);
            std::cout << "E: " << E << "\n";
            this->adjacency_list = std::vector<std::vector<std::pair<size_t, int>>>(this->V);       
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


Graph::Graph(size_t V){
    this->V = V;
    this->adjacency_list = std::vector<std::vector<std::pair<size_t, int>>>(V);
}


void Graph::add_edge(size_t a, size_t b, int weight){
    this->adjacency_list[a].push_back(std::make_pair(b, weight));
}


void Graph::print_graph(){
    // increasing by one to make vertices start from1 instead of 0,
    // to match vector convention
    for(int i=0; i<this->adjacency_list.size(); i++){
        std::cout << i + 1 << ":\t";
        for(int j=0; j<this->adjacency_list[i].size(); j++){
            std::cout << "(" << adjacency_list[i][j].first + 1 << ", " << adjacency_list[i][j].second<< "), ";
        }
        std::cout << "\n";
    }
}