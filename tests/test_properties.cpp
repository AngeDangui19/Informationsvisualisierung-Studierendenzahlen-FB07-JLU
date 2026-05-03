#include <catch2/catch_test_macros.hpp>
#include "graph/properties.hpp"

TEST_CASE("Graph properties") {
    DirectedGraph dg;

    auto v0 = dg.add_vertex();
    auto v1 = dg.add_vertex();

    dg.add_edge(v0, v1);

    REQUIRE(graph::is_dag(dg));

    UndirectedGraph ug;
    auto u0 = ug.add_vertex();
    auto u1 = ug.add_vertex();

    ug.add_edge(u0, u1);

    REQUIRE(graph::is_tree(ug));
}