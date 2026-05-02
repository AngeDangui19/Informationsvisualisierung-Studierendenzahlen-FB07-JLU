#include "graph/weighted_directed_graph.hpp"

#include <iostream>
#include <fstream>

int main() {
    WeightedDirectedGraph graph;

    auto v0 = graph.add_vertex("v0");
    auto v1 = graph.add_vertex("v1");
    auto v2 = graph.add_vertex("v2");

    graph.add_edge(v0, v1, 4.0, "e0");
    graph.add_edge(v0, v2, 2.0, "e1");
    graph.add_edge(v2, v1, 1.0, "e2");

    std::cout << "Vertices:\n";
    for (auto v : graph) {
        std::cout << v << " -> "
                  << graph.vertex_property(v).name << '\n';
    }

    std::cout << "\nEdges:\n";
    for (auto from : graph) {
        for (const auto& edge : graph.neighbors(from)) {
            std::cout << graph.vertex_property(from).name
                      << " -> "
                      << graph.vertex_property(edge.to).name
                      << " | weight = "
                      << edge.weight;

            if (!edge.label.empty()) {
                std::cout << " | label = " << edge.label;
            }

            std::cout << '\n';
        }
    }

    return 0;
}