#ifndef LAB1_ALGORITHMS_HPP
#define LAB1_ALGORITHMS_HPP

#include <vector>
#include <tuple>
#include <string>


class TreeNode{
    public:
    int value;
    std::vector<TreeNode*> children;

    TreeNode(int value, std::vector<TreeNode*> children);
};


void PrintVectorInt(std::vector<int> v);


/**
 * Pretty prints a tree stored in form of a parents vector
 */
void print_parents(std::vector<int> parents);


std::vector<std::vector<int>> graph_from_file(std::string input_path);


/**
 * Input: graph in the form of an adjecency matrix represented by a 2d vector
 * Returns: a pair containing:
 *      a vector of nodes in the order of visiting
 *      a search tree in form of parents vector
 */
std::pair<std::vector<int>, std::vector<int>> DFS(std::vector<std::vector<int>> graph);


/**
 * Input: graph in the form of an adjecency matrix represented by a 2d vector
 * Returns: a pair containing:
 *      a vector of nodes in the order of visiting
 *      a search tree in form of parents vector
 */
std::pair<std::vector<int>, std::vector<int>> BFS(std::vector<std::vector<int>> graph);


/**
 * Input: graph in the form of an adjecency matrix represented by a 2d vector
 * Returns: a pair containing:
 *      a boolean value answering if there exists a directed cycle in the graph
 *      a topoligocally sorted list of vertices in form of a vector
 */
std::pair<bool, std::vector<int>> topo_sort(std::vector<std::vector<int>> graph);


/**
 * Input: graph in the form of an adjecency matrix represented by a 2d vector
 * Returns: the graph seperated into strongly connected components
 * stored in the form of a vector of vectors
 */
std::vector<std::vector<int>> SCC(std::vector<std::vector<int>> graph);



/**
 * Input: graph in the form of an adjecency matrix represented by a 2d vector
 * Returns: a pair containing:
 *      a boolean value answering if the graph is bipartite
 *      a pair of vectors representing the partitions of the graph
 */
std::pair<bool, std::pair<std::vector<int>, std::vector<int>>> bipartition(
    std::vector<std::vector<int>> graph); 


#endif  // LAB1_ALGORITHMS_HPP

