cmake_minimum_required(VERSION 3.10)
project(GraphAlgorithms)

add_executable(DFS ./src/DFS.cpp ./src/graph_alg.cpp)
add_executable(BFS ./src/BFS.cpp ./src/graph_alg.cpp)
add_executable(topo_sort ./src/topo_sort.cpp ./src/graph_alg.cpp)
add_executable(SCC ./src/SCC.cpp ./src/graph_alg.cpp)
add_executable(bipartite ./src/bipartite.cpp ./src/graph_alg.cpp)