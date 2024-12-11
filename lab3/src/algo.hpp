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
            int vertex;
            int dist;
        };

        using bucket_t = std::vector<node>;
        int size;   // number of buckets
        std::vector<bucket_t> buckets;
        std::vector<std::pair<int, int>> ranges;
        int current_min;

        int get_bucket_index(int dist) const;

    public:
        Radix_Heap(int max_dist);

        void insert(int vertex, int dist);
        std::pair<int, int> extract_first();
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
        Graph(int V);
        
        int V; /* Number of vertices */
        int E; /* Nmber of edges */
        int max_weight; /* Highest weight of all edges */

        /**
         * Adjacency list representing a graph.
         * Edges and weights are stored in form of a pair (vertex, weight)
         */ 
        std::vector<std::vector<std::pair<int, int>>> adjacency_list;

        /**
         * Ads an edge to the adjacency list
         * with a weight
         */
        void add_edge(int a, int b, int weight);

        /**
         * Neatly prints the adjacency list
         */
        void print_graph();

        /**
         * Parses a text file to create a list of nodes
         * that will be sources in the ss variant of pahfinding
         * @param ss_path path to the input file
         */
        std::vector<int> ss_from_file(std::string ss_path);

        /**
         * @brief Parses a text file to create a list of pairs of vertices
         * between which we will find the shortest path
         * @param p2p_path path to the input file
         */
        std::vector<std::pair<int, int>> p2p_from_file(std::string p2p_path);

        void ss_result(int V, int E, std::pair<int, int> range, int avg_time,
                    std::string data_path, std::string ss_path, std::string result_path);

        void p2p_result(int V, int E, std::vector<std::tuple<int, int, int>> dists,
                    std::pair<int, int> range, int avg_time,
                    std::string data_path, std::string p2p_path, std::string result_path);

        /**
         * @brief Finds shortest paths between source and all other nodes
         * 
         * Assumes that wieghts are integer, non-negative values
         * @param source source node
         * @return a vector of shortest path distances from source to other vertices
         */
        std::vector<int> dijkstra(int source);

        /**
         * @brief Finds shortest paths between source and all other nodes
         * 
         * Assumes that wieghts are integer, non-negative values
         * @param source source node
         * @return a vector of shortest path distances from source to other vertices
         */
        std::vector<int> dial(int source);

        /**
         * @brief Finds shortest paths between source and all other nodes
         * 
         * Assumes that wieghts are integer, non-negative values
         * @param source source node
         * @return a vector of shortest path distances from source to other vertices
         */
        std::vector<int> radix(int source);

};


#endif /* SRC_ALGO_INCLUDED */