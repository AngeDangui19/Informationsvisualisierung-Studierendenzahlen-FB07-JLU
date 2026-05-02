#include "graph/weighted_directed_graph.hpp"
#include "graph/algorithms/shortest_path.hpp"

#include <iostream>

int main() {
    WeightedDirectedGraph graph;

    auto v0 = graph.add_vertex("v0");
    auto v1 = graph.add_vertex("v1");
    auto v2 = graph.add_vertex("v2");
    auto v3 = graph.add_vertex("v3");

    graph.add_edge(v0, v1, 4.0);
    graph.add_edge(v0, v2, 5.0);
    graph.add_edge(v1, v2, -2.0);
    graph.add_edge(v2, v3, 3.0);

    auto dist = graph::bellman_ford(graph, v0);

    std::cout << "Bellman-Ford distances from v0:\n";

    for (std::size_t i = 0; i < dist.size(); ++i) {
        std::cout << "v" << i << " = " << dist[i] << '\n';
    }

    return 0;
}