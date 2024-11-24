#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "algo.hpp"


Graph::Graph(std::string input_path){
    std::ifstream input(input_path);
    std::string line;

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
            // decerasing by one to make vertices start from 0 instead of 1, to match vector convention
            add_edge(stoul(words[1]) - 1, stoul(words[2]) - 1, stoul(words[3]));
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


void Graph::print_graph(){
    // increasing by one to make vertices start from1 instead of 0,
    // to match vector convention
    for(size_t i=0; i<this->adjacency_list.size(); i++){
        std::cout << i + 1 << ":\t";
        for(size_t j=0; j<this->adjacency_list[i].size(); j++){
            std::cout << "(" << adjacency_list[i][j].first + 1 << ", " << adjacency_list[i][j].second<< "), ";
        }
        std::cout << "\n";
    }
}


std::vector<size_t> Graph::ss_from_file(std::string ss_path){
    std::vector<size_t> ss_vector(0);
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
            p2p_vector.push_back(std::make_pair(stoul(words[1]), stoul(words[2])));
        }
    }   
    return p2p_vector;    
}


std::vector<size_t> Graph::dijkstra(size_t source){}


std::vector<size_t> Graph::dial(size_t source){}


std::vector<size_t> Graph::radixheap(size_t source){}