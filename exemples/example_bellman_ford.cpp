#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

int main() {
    WeightedDirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_vertex();

    graph.add_edge(0, 1, 4.0);
    graph.add_edge(0, 2, 1.0);
    graph.add_edge(2, 1, 2.0);

    const auto distances = bellman_ford(graph, 0);

    std::cout << "Bellman-Ford distances:\n";
    for (std::size_t i = 0; i < distances.size(); ++i) {
        std::cout << "0 -> " << i << " = " << distances[i] << '\n';
    }

    return 0;
}