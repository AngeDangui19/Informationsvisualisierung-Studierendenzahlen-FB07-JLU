#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

#include <cassert>
#include <cstddef>

int main() {
    {
        graph::DirectedGraph g;

        const auto a = g.add_vertex();
        const auto b = g.add_vertex();

        g.add_edge(a, b);

        assert(g.vertex_count() == 2);
        assert(g.edge_count() == 1);
        assert(g.neighbors(a).size() == 1);
        assert(g.neighbors(b).empty());
    }

    {
        graph::UndirectedGraph g;

        const auto a = g.add_vertex();
        const auto b = g.add_vertex();

        g.add_edge(a, b);

        assert(g.vertex_count() == 2);
        assert(g.edge_count() == 1);
        assert(g.neighbors(a).size() == 1);
        assert(g.neighbors(b).size() == 1);
    }

    {
        graph::WeightedDirectedGraph g;

        const auto a = g.add_vertex();
        const auto b = g.add_vertex();

        g.add_edge(a, b, 4.5);

        assert(g.vertex_count() == 2);
        assert(g.edge_count() == 1);
        assert(g.weighted_neighbors(a).size() == 1);
    }

    {
        graph::WeightedUndirectedGraph g;

        const auto a = g.add_vertex();
        const auto b = g.add_vertex();

        g.add_edge(a, b, 7.0);

        assert(g.vertex_count() == 2);
        assert(g.edge_count() == 1);
        assert(g.weighted_neighbors(a).size() == 1);
        assert(g.weighted_neighbors(b).size() == 1);
    }

    return 0;
}