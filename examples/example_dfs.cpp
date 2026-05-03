#include "graph/directed_graph.hpp"
#include "graph/algorithms/traversal.hpp"

#include <iostream>

int main() {
    DirectedGraph graph;

    auto v0 = graph.add_vertex();
    auto v1 = graph.add_vertex();
    auto v2 = graph.add_vertex();
    auto v3 = graph.add_vertex();
    auto v4 = graph.add_vertex();
    auto v5 = graph.add_vertex();

    graph.add_edge(v0, v1);
    graph.add_edge(v0, v2);
    graph.add_edge(v1, v3);
    graph.add_edge(v1, v4);
    graph.add_edge(v2, v5);

    auto order = graph::dfs(graph, v0);

    std::cout << "DFS traversal from v0:\n";

    for (auto vertex : order) {
        std::cout << "v" << vertex << " ";
    }

    std::cout << '\n';

    return 0;
}