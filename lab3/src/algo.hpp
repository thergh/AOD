#ifndef SRC_ALGO_INCLUDED
#define SRC_ALGO_INCLUDED

#include <vector>
#include <string>


template <typename T>
void print_vector(const std::vector<T>& v){
    std::cout << "[ ";
    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << "]\n";
}


class Radix_Heap{
    private:
        struct node{
            size_t vertex;
            size_t dist;
        };

        using bucket_t = std::vector<node>;
        size_t size;   // number of buckets
        std::vector<bucket_t> buckets;
        std::vector<std::pair<size_t, size_t>> ranges;
        size_t current_min;

        size_t get_bucket_index(size_t dist) const;

    public:
        Radix_Heap(size_t max_dist);

        void insert(size_t vertex, size_t dist);
        std::pair<size_t, size_t> extract_first();
    bool empty() const;
};


class Graph{
    public:
        /**
         * Constructs a graph represented by an adjacency list
         * by parsing a text file
         */
        Graph(std::string input_path);

        /**
         * Temp debug constructor
         */
        Graph(size_t V);
        
        size_t V; /* Number of vertices */
        size_t E; /* Nmber of edges */
        size_t max_weight; /* Highest weight of all edges */

        /**
         * Adjacency list representing a graph.
         * Edges and weights are stored in form of a pair (vertex, weight)
         */ 
        std::vector<std::vector<std::pair<size_t, size_t>>> adjacency_list;

        /**
         * Ads an edge to the adjacency list
         * with a weight
         */
        void add_edge(size_t a, size_t b, size_t weight);

        /**
         * Neatly prsize_ts the adjacency list
         */
        void prsize_t_graph();

        /**
         * Parses a text file to create a list of nodes
         * that will be sources in the ss variant of pahfinding
         * @param ss_path path to the input file
         */
        std::vector<size_t> ss_from_file(std::string ss_path);

        /**
         * @brief Parses a text file to create a list of pairs of vertices
         * between which we will find the shortest path
         * @param p2p_path path to the input file
         */
        std::vector<std::pair<size_t, size_t>> p2p_from_file(std::string p2p_path);

        void ss_result(size_t V, size_t E, std::pair<size_t, size_t> range, size_t avg_time,
                    std::string data_path, std::string ss_path, std::string result_path);

        void p2p_result(size_t V, size_t E, std::vector<std::tuple<size_t, size_t, size_t>> dists,
                    std::pair<size_t, size_t> range, size_t avg_time,
                    std::string data_path, std::string p2p_path, std::string result_path);

        /**
         * @brief Finds shortest paths between source and all other nodes
         * 
         * Assumes that wieghts are size_teger, non-negative values
         * @param source source node
         * @return a vector of shortest path distances from source to other vertices
         */
        std::vector<size_t> dijkstra(size_t source);

        /**
         * @brief Finds shortest paths between source and all other nodes
         * 
         * Assumes that wieghts are size_teger, non-negative values
         * @param source source node
         * @return a vector of shortest path distances from source to other vertices
         */
        std::vector<size_t> dial(size_t source);

        /**
         * @brief Finds shortest paths between source and all other nodes
         * 
         * Assumes that wieghts are size_teger, non-negative values
         * @param source source node
         * @return a vector of shortest path distances from source to other vertices
         */
        std::vector<size_t> radix(size_t source);

};


#endif /* SRC_ALGO_INCLUDED */