#include <catch2/catch_test_macros.hpp>
#include "graph/undirected_graph.hpp"
#include "graph/algorithms/connectivity.hpp"

TEST_CASE("Connected components") {
    UndirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v2, v3);

    auto comps = graph::connected_components(g);

    REQUIRE(comps.size() == 2);
}