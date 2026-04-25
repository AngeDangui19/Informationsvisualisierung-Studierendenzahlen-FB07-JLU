#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/weighted_undirected_graph.hpp"

int main()
{
    WeightedUndirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, -2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto mst = prim(g, v0);

    double total_weight = 0.0;

    std::cout << "Prim MST edges:\n";
    for (const auto& edge : mst) {
        std::cout << edge.from << " -- " << edge.to
                  << " (w=" << edge.weight << ")\n";
        total_weight += edge.weight;
    }

    std::cout << "Total MST weight: " << total_weight << '\n';

    return 0;
}