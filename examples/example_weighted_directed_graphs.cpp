#include "graph/weighted_directed_graph.hpp"

#include <fstream>
#include <iostream>

int main() {
    WeightedDirectedGraph graph;

    auto v0 = graph.add_vertex();
    auto v1 = graph.add_vertex();
    auto v2 = graph.add_vertex();

    graph.add_edge(v0, v1, 10.0);
    graph.add_edge(v0, v2, 5.0);

    std::cout << "Vertex count: " << graph.vertex_count() << '\n';
    std::cout << "Edge count: " << graph.edge_count() << '\n';

    std::cout << "\nVertices:\n";
    for (auto vertex : graph) {
        std::cout << vertex << " = "
                  << graph.vertex_property(vertex).name << '\n';
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

    std::ofstream file("../../logbook_graphs/graph_without_labels.dot");
    graph.to_graphviz(file);

    std::cout << "Graph written to logbook_graphs/graph_without_labels\n";

    return 0;
}