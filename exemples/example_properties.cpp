#include <iostream>

#include "graph/properties.hpp"
#include "graph/directed_graph.hpp"

int main() {
    DirectedGraph graph;
    graph.add_vertex();

    std::cout << std::boolalpha;
    std::cout << "is_dag: " << is_dag(graph) << '\n';

    return 0;
}