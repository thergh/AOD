#ifndef SRC_ALGO_HPP
#define SRC_ALGO_HPP


#include <vector>
#include <map>
#include <iostream>


template <typename T>
void print_vector(const std::vector<T>& v){
    std::cout << "[ ";
    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << "]\n";
}


class Hypercube{
    public:
        Hypercube(int k);

        typedef std::vector<std::vector<int>> vv_t;
        typedef std::map<std::pair<int, int>, int> m_t;
        
        int k;
        std::vector<std::vector<int>> adj_list;
        std::map<std::pair<int, int>, int> capacities;

        void generate_caps();
        void max_flow();

    private:
        m_t flow;
};

#endif