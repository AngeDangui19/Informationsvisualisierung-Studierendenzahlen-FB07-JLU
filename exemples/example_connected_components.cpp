#include <iostream>

#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

int main() {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    const auto components = connected_components(graph);

    std::cout << "Connected components: " << components.size() << '\n';
    return 0;
}