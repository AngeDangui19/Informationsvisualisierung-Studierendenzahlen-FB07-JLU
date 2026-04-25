#include "graph/properties.hpp"

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

#include <cassert>
#include <cstddef>

int main() {
    {
        graph::DirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1);
        g.add_edge(1, 2);

        assert(graph::is_dag(g));
    }

    {
        graph::UndirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1);
        g.add_edge(1, 2);

        assert(graph::is_tree(g));
    }

    {
        graph::WeightedDirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1, 2.5);
        g.add_edge(1, 2, 3.0);

        assert(graph::has_only_positive_weights(g));
    }

    {
        graph::WeightedUndirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1, 1.0);
        g.add_edge(1, 2, 2.0);

        assert(graph::is_connected(g));
    }

    return 0;
}