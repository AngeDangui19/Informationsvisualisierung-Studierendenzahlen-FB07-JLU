#include "graph/properties.hpp"

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

#include <cstddef>
#include <iostream>

int main() {
    {
        graph::DirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1);
        g.add_edge(1, 2);

        std::cout << "Directed graph is DAG: "
                  << graph::is_dag(g) << '\n';
    }

    {
        graph::UndirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1);
        g.add_edge(1, 2);

        std::cout << "Undirected graph is tree: "
                  << graph::is_tree(g) << '\n';
    }

    {
        graph::WeightedDirectedGraph g;

        for (std::size_t i = 0; i < 2; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1, 5.0);

        std::cout << "Weighted directed graph has only positive weights: "
                  << graph::has_only_positive_weights(g) << '\n';
    }

    {
        graph::WeightedUndirectedGraph g;

        for (std::size_t i = 0; i < 3; ++i) {
            g.add_vertex();
        }

        g.add_edge(0, 1, 1.0);
        g.add_edge(1, 2, 2.0);

        std::cout << "Weighted undirected graph is connected: "
                  << graph::is_connected(g) << '\n';
    }

    return 0;
}