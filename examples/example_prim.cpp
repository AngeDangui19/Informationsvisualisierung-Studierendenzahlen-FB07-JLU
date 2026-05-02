#include "graph/weighted_undirected_graph.hpp"
#include "graph/algorithms/mst.hpp"

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

    auto mst = graph::prim(graph, v0);

    std::cout << "Prim MST:\n";

    for (const auto& [from, to, weight] : mst) {
        std::cout << graph.vertex_property(from).name
                  << " -- "
                  << graph.vertex_property(to).name
                  << " | weight = "
                  << weight
                  << '\n';
    }

    return 0;
}