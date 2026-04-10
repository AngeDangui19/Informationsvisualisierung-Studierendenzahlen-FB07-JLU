#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

int main() {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    const auto result = dfs(graph, 0);

    std::cout << "DFS visited " << result.size() << " vertices.\n";
    return 0;
}