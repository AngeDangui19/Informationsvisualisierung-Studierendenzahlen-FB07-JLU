#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

#include <cstddef>
#include <iostream>

int main() {
    graph::UndirectedGraph g;

    for (std::size_t i = 0; i < 6; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    const auto components = graph::connected_components(g);

    std::cout << "Connected components:\n";

    for (std::size_t i = 0; i < components.size(); ++i) {
        std::cout << "Component " << i << ": ";

        for (const auto vertex : components[i]) {
            std::cout << vertex << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}