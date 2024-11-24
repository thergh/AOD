#ifndef SRC_ALGO_INCLUDED
#define SRC_ALGO_INCLUDED

#include <vector>
#include <string>

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
         * Neatly prints the adjacency list
         */
        void print_graph();

        /**
         * Parses a text file to create a list of nodes
         * that will be sources in the ss variant of pahfinding
         */
        std::vector<size_t> ss_from_file(std::string ss_path);

        /**
         * Parses a text file to create a list of pairs of vertices
         * between which we will find the shortest path
         */
        std::vector<std::pair<size_t, size_t>> p2p_from_file(std::string p2p_path);

        /**
         * Finds shortest paths between source and all other nodes
         * Assumes that:
         *      - wieghts have integer, non-negative values
         */
        std::vector<size_t> dijkstra(size_t source);

        std::vector<size_t> dial(size_t source);

        std::vector<size_t> radixheap(size_t source);
};

#endif /* SRC_ALGO_INCLUDED */ 