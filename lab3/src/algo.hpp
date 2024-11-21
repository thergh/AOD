#ifndef SRC_ALGO_INCLUDED
#define SRC_ALGO_INCLUDED

#include <vector>


class Graph{
    public:
        const size_t V; // Number of vertices
        const size_t E; // Number of edges
        int max_weight; // Highest weight of all edges

        // Adjacency list representing a graph.
        // Edges and weights are stored in form of a pair (vertex, weight)
        std::vector<std::vector<std::pair<size_t, int>>> adjacency_list;

        void add_edge(size_t a, size_t b, int weight);
};

#endif // SRC_ALGO_INCLUDED