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
    graph.add_edge(v0, v2, 1.0);
    graph.add_edge(v2, v1, 2.0);
    graph.add_edge(v1, v3, 1.0);
    graph.add_edge(v2, v3, 5.0);

    auto result = graph::dijkstra(graph, v0);

    std::cout << "Dijkstra shortest paths from v0:\n";

    for (auto vertex : graph) {
        std::cout << graph.vertex_property(vertex).name
                  << " | distance = "
                  << result.distances[vertex]
                  << " | path = ";

        auto path = graph::reconstruct_path<WeightedDirectedGraph>(
            vertex,
            result.parents
        );

        for (std::size_t i = 0; i < path.size(); ++i) {
            std::cout << graph.vertex_property(path[i]).name;

            if (i + 1 < path.size()) {
                std::cout << " -> ";
            }
        }

        std::cout << '\n';
    }

    return 0;
}