#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/weighted_undirected_graph.hpp"

int main() {
    WeightedUndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1, 1.0);

    const auto mst = prim(graph, 0);

    std::cout << "Prim MST edges: " << mst.edge_count() << '\n';
    return 0;
}