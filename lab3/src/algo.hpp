#ifndef SRC_ALGO_INCLUDED
#define SRC_ALGO_INCLUDED

#include <vector>
#include <string>

class Graph{
    public:
        Graph(std::string input_path);
        Graph(size_t V);

        size_t V; // Number of vertices
        size_t E; // Number of edges
        int max_weight; // Highest weight of all edges

        // Adjacency list representing a graph.
        // Edges and weights are stored in form of a pair (vertex, weight)
        std::vector<std::vector<std::pair<size_t, int>>> adjacency_list;

        void add_edge(size_t a, size_t b, int weight);

        void print_graph();
};

#endif // SRC_ALGO_INCLUDED