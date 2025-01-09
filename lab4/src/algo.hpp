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


class Hypercube{
    public:
        Hypercube(int k);

        typedef std::vector<std::vector<int>> vv_t;
        typedef std::map<std::pair<int, int>, int> m_t;
        
        const int k;
        std::vector<std::vector<int>> adj_list;
        std::map<std::pair<int, int>, int> capacities;

        void generate_caps();
        void max_flow();
        void display_adj();

    private:
        m_t flow;
};

#endif