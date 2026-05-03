#include "graph/undirected_graph.hpp"
#include "graph/algorithms/connectivity.hpp"
#include <iostream>

int main() {
    UndirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v2, v3);

    auto comps = graph::connected_components(g);

    for (const auto& comp : comps) {
        for (auto v : comp)
            std::cout << v << " ";
        std::cout << "\n";
    }
}