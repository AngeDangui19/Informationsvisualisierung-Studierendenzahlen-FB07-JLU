#include "graph/weighted_undirected_graph.hpp"

#include <fstream>
#include <iostream>

int main() {
    WeightedUndirectedGraph graph;

    auto v0 = graph.add_vertex("v0");
    auto v1 = graph.add_vertex("v1");
    auto v2 = graph.add_vertex("v2");
    auto v3 = graph.add_vertex("v3");

    graph.add_edge(v0, v1, 1.0, "e0");
    graph.add_edge(v0, v2, 4.0, "e1");
    graph.add_edge(v1, v2, 2.0, "e2");
    graph.add_edge(v1, v3, 5.0, "e3");
    graph.add_edge(v2, v3, 3.0, "e4");

    std::cout << "Vertex count: " << graph.vertex_count() << '\n';
    std::cout << "Edge count: " << graph.edge_count() << '\n';

    std::cout << "\nEdges:\n";

    for (auto from : graph) {
        for (const auto& edge : graph.neighbors(from)) {
            if (from <= edge.to) {
                std::cout << graph.vertex_property(from).name
                          << " -- "
                          << graph.vertex_property(edge.to).name
                          << " | weight = "
                          << edge.weight;

                if (!edge.label.empty()) {
                    std::cout << " | label = " << edge.label;
                }

                std::cout << '\n';
            }
        }
    }

    std::ofstream file("../../logbook_graphs/weighted_undirected_graph.dot");
    graph.to_graphviz(file);

    std::cout << "\nGraph written to ../../logbook_graphs/weighted_undirected_graph.dot\n";

    return 0;
}