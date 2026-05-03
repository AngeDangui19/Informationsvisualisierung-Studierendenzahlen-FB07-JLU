#include "graph/directed_graph.hpp"
#include "graph/algorithms/traversal.hpp"
#include <iostream>

int main() {
    DirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);

    auto order = graph::bfs(g, v0);

    for (auto v : order)
        std::cout << v << " ";
}