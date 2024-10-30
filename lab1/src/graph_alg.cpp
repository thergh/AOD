#include "graph_alg.hpp"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>



TreeNode::TreeNode(int value, std::vector<TreeNode*> children){
        this->value = value;
        this->children = children;
    }


void PrintVectorInt(std::vector<int> v) {
	for(int i = 0; i < v.size(); i++) {
		std::cout << v[i] + 1 << " ";
	}
	std::cout << std::endl;
}


void PrintVectorBool(std::vector<bool> v) {
	for(int i = 0; i < v.size(); i++) {
		std::cout << v[i] + 1 << " ";
	}
	std::cout << std::endl;
}


void tree_from_parents(const std::vector<int>& parents, std::vector<std::vector<int>>& tree){
    for(int i=1; i<parents.size(); i++){
        tree[parents[i]].push_back(i);
    }
}


void print_tree(const std::vector<std::vector<int>>& tree, int node, int depth){
    for(int i=0; i<depth; i++){
        std::cout << "  ";
    }

    // adding +1 to comply with data
    std::cout << node + 1 << std::endl;

    for(int child : tree[node]){
        print_tree(tree, child, depth + 1);
    }
}


void print_parents(std::vector<int> parents){
    std::vector<std::vector<int>> tree(parents.size());
    tree_from_parents(parents, tree);
    print_tree(tree, 0, 0);
}


std::vector<std::vector<int>> graph_from_file(std::string input_path){
    std::ifstream input_file(input_path);
    if(!input_file){
        std::cout << "Error: wrong input file path.\n";
        return std::vector<std::vector<int>>();
    }

    std::string line;
    bool is_directed;
    
    std::getline(input_file, line);
    
    char first_char = line[0];
    if(first_char == 'D'){
        is_directed = true;
    }
    else{
        is_directed = false;
    }

    std::getline(input_file, line);
    int v = std::stoi(line);    // number of vertices
    std::vector<std::vector<int>> graph(v, std::vector<int>()); // init. adj. matrix

    std::getline(input_file, line);
    int e = std::stoi(line);    // number of edges

    while(std::getline(input_file, line)){
        int edge_a;
        int edge_b;

        std::istringstream word_stream(line);

        word_stream >> edge_a;
        word_stream >> edge_b;

        // here I do -1 to enable counting from 0 instead from 1
        // It will be necessary to revert it when printing the results
        // but it will save me the headache of off-by-1 errors
        edge_a --;
        edge_b --;

        graph[edge_a].push_back(edge_b);
        if(!is_directed){
            graph[edge_b].push_back(edge_a);
        }
    }

    return graph;
}


std::pair<std::vector<int>, std::vector<int>> DFS(std::vector<std::vector<int>> graph){
    std::vector<bool> visited = std::vector<bool>(graph.size(), false);
    std::stack<int> stack;
    std::vector<int> path;
    std::vector<int> parents(graph.size(), -1);
    std::pair<std::vector<int>, std::vector<int>> result;

    stack.push(0);
    visited[0] = true;
    parents[0] = -1;

    while(!stack.empty()){
        int vertex = stack.top();
        stack.pop();
        visited[vertex] = true;
        
        // Adding all neighbours of vertex to the stack
        for(int i=0; i<graph[vertex].size(); i++){
            if(!visited[graph[vertex][i]]){
                stack.push(graph[vertex][i]);
                visited[graph[vertex][i]] = true;
                parents[graph[vertex][i]] = vertex;
            }
        }
        path.push_back(vertex);
    }

    result.first = path;
    result.second = parents;
    return result;
}


std::pair<std::vector<int>, std::vector<int>> BFS(std::vector<std::vector<int>> graph){
    std::vector<bool> visited = std::vector<bool>(graph.size(), false);
    std::queue<int> queue;
    std::vector<int> path;
    std::vector<int> parents(graph.size(), -1);
    std::pair<std::vector<int>, std::vector<int>> result;

    queue.push(0);
    visited[0] = true;
    parents[0] = -1;

    while(!queue.empty()){
        int vertex = queue.front();
        queue.pop();
        visited[vertex] = true;
        
        // Adding all neighbours of vertex to the stack
        for(int i=0; i<graph[vertex].size(); i++){
            if(!visited[graph[vertex][i]]){
                queue.push(graph[vertex][i]);
                visited[graph[vertex][i]] = true;
                parents[graph[vertex][i]] = vertex;
            }
        }
        path.push_back(vertex);
    }

    result.first = path;
    result.second = parents;
    return result;
}


// kahn's version
std::pair<bool, std::vector<int>> topo_sort(const std::vector<std::vector<int>> graph){
    int n = graph.size();
    std::vector<int> in_degree(n, 0); 
    std::vector<int> topo_order;

    // computing the in-degrees
    for(int i=0; i<n; i++){
        for(int neighbor : graph[i]){
            in_degree[neighbor]++;
        }
    }

    // queueing vertices with indegrees 0
    std::queue<int> q;
    for(int i=0; i<n; i++){
        if(in_degree[i] == 0){
            q.push(i);
        }
    }

    // processing the queue
    while(!q.empty()){
        int node = q.front();
        q.pop();
        topo_order.push_back(node);

        for(int neighbor : graph[node]){
            // decreasing indegree, removing edge
            in_degree[neighbor]--;
            // if in-degree becomes 0, add it to the queue
            if(in_degree[neighbor] == 0){
                q.push(neighbor);
            }
        }
    }

    // checking for a cycle
    if(topo_order.size() == n){
        return {false, topo_order};  // no cycle, all good
    }
    else{
        return {true, {}};  // cycle found
    }
}


void SCC_util(std::vector<std::vector<int>> graph,
        int vertex, std::vector<int>& disc_times, std::vector<int>& min_disc,
        std::stack<int>& stack, std::vector<bool>& on_stack,
        std::vector<std::vector<int>> components){

    static int time = 0;
    stack.push(vertex);
    on_stack[vertex] = true;

    // iterate over all vertices adjecent to vertex
    for(int i=0; i<graph[i].size(); i++){
        // if a vertex is not yet visited, recur on it
        if(on_stack[i] == false){
            SCC_util(graph, i, disc_times, min_disc, stack, on_stack, components);
            min_disc[vertex] = std::min(min_disc[vertex], min_disc[i]);
        }
        else if(on_stack[i] == true){
            min_disc[vertex] = std::min(min_disc[vertex], disc_times[i]);
        }
    }
    // finish

    int w = 0;
    if(min_disc[vertex] = disc_times[vertex]){
        while(stack.top() != vertex){
            w = stack.top();
            std::cout << w << " ";
            on_stack[w] = false;
            stack.pop();
        }
        w = stack.top();
        std::cout << w << "\n";
        on_stack[w] = false;
        stack.pop();
    }

}


// // TODO: REDO
std::vector<std::vector<int>> SCC(std::vector<std::vector<int>> graph){
    int n = graph.size();
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(n, false);
    std::stack<int> stack;

    std::vector<int> disc_times(n, -1); // discovery times of vertices
    std::vector<int> min_disc(n, -1);    // vertex with min discovery time from each vertex
    std::vector<bool> on_stack(n, false);   // true if the vertex is on stack

    // calling the recursive function on all unvisited vertices
    for(int i=0; i<n; i++){
        if(disc_times[i] == -1){
            SCC_util(graph, i, disc_times, min_disc, stack, on_stack, components);
        }
    }
    PrintVectorBool(visited);
    return components;
}

std::pair<bool, std::pair<std::vector<int>, std::vector<int>>> bipartition(
        std::vector<std::vector<int>> graph){

        int v = graph.size();
    std::stack<int> stack;
    std::vector<int> path;
    std::vector<int> colors(v, 0);
    std::vector<int> positive_vertices;
    std::vector<int> negative_vertices;

    std::pair<std::vector<int>, std::vector<int>> partitions;
    std::pair<bool, std::pair<std::vector<int>, std::vector<int>>> result;

    stack.push(0);
    colors[0] = 1;

    while(!stack.empty()){
        int vertex = stack.top();
        stack.pop();
        int current_color = colors[vertex];
        
        // Adding all neighbours of vertex to the stack
        for(int i=0; i<graph[vertex].size(); i++){
            if(colors[graph[vertex][i]] == current_color){  // color collision
                result.first = false;
                return result;     
            }
            else if(colors[graph[vertex][i]] == 0){         // not yet colored
                colors[graph[vertex][i]] = current_color * (-1);
                stack.push(graph[vertex][i]);
            }
            else{   // if the colors are different, everything's ok

            }
        }
        
        // adding the vertex to the correct partition
        if(colors[vertex] == 1){
            positive_vertices.push_back(vertex);
        }
        else{
            negative_vertices.push_back(vertex); 
        }
    }

    partitions.first = positive_vertices;
    partitions.second = negative_vertices;
    result.first = true;
    result.second = partitions;
    return result;
}
