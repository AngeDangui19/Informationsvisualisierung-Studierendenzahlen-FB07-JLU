#include <catch2/catch_test_macros.hpp>
#include "graph/directed_graph.hpp"
#include "graph/algorithms/traversal.hpp"

TEST_CASE("DFS traversal") {
    DirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);

    auto order = graph::dfs(g, v0);

    REQUIRE(order[0] == v0);
    REQUIRE(order.size() == 3);
}