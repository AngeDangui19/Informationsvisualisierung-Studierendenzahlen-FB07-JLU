#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

int main() {
    WeightedDirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1, 2.0);

    const auto distances = dijkstra(graph, 0);

    std::cout << "Distance vector size: " << distances.size() << '\n';
    return 0;
}