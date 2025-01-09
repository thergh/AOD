#ifndef SRC_ALGO_HPP
#define SRC_ALGO_HPP


#include <vector>
#include <map>
#include <iostream>


template <typename T>
void display_vector(const std::vector<T>& v){
    std::cout << "[ ";
    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << "]\n";
}


template <typename T>
void display_2dvector(const std::vector<std::vector<T>>& v){
    for(auto x : v){
        std::cout << "[ ";
        for(auto y : x){
            std::cout << y << " ";
        }
        std::cout << "]\n";
    }
}


class Graph{
    public:
        Graph();

        typedef std::vector<std::vector<int>> vv_t;
        typedef std::map<std::pair<int, int>, int> m_t;
        
        std::vector<std::vector<int>> adj_list;
        std::map<std::pair<int, int>, int> capacities;

        void gen_hypercube(int k);
        void gen_bipartite(int k, int i);
        int max_flow();
        void display_adj();

    private:
        m_t flow;
};

#endif