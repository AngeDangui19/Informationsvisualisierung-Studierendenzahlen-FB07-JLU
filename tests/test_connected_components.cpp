#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

#include <cassert>
#include <cstddef>
#include <vector>

int main() {
    graph::UndirectedGraph g;

    for (std::size_t i = 0; i < 6; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1);
    g.add_edge(1, 2);

    g.add_edge(3, 4);

    const auto components = graph::connected_components(g);

    assert(components.size() == 3);

    return 0;
}