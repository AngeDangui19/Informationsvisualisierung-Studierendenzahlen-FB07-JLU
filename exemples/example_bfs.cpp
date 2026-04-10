#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

int main() {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    const auto result = bfs(graph, 0);

    std::cout << "BFS visited " << result.size() << " vertices.\n";
    return 0;
}