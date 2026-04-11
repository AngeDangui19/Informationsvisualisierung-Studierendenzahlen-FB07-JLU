#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/directed_graph.hpp"

int main() {
    DirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    const auto order = topological_sort(graph);

    std::cout << "Topological order size: " << order.size() << '\n';
    return 0;
}