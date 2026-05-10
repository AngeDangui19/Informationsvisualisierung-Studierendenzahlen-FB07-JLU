#include <catch2/catch_test_macros.hpp>
#include "graph/directed_graph.hpp"
#include "graph/algorithms/traversal.hpp"

TEST_CASE("Topological sort on linear chain") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);

    auto order = graph::topological_sort(g);

    REQUIRE(order[0] == v0);
    REQUIRE(order[1] == v1);
    REQUIRE(order[2] == v2);
}

TEST_CASE("Topological sort respects dependencies") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v2);
    g.add_edge(v1, v2);
    g.add_edge(v2, v3);

    auto order = graph::topological_sort(g);

    REQUIRE(order.size() == 4);

    auto pos_v0 = std::find(order.begin(), order.end(), v0) - order.begin();
    auto pos_v1 = std::find(order.begin(), order.end(), v1) - order.begin();
    auto pos_v2 = std::find(order.begin(), order.end(), v2) - order.begin();
    auto pos_v3 = std::find(order.begin(), order.end(), v3) - order.begin();

    REQUIRE(pos_v0 < pos_v2);
    REQUIRE(pos_v1 < pos_v2);
    REQUIRE(pos_v2 < pos_v3);
}

TEST_CASE("Topological sort on single vertex") {
    DirectedGraph g;
    auto v0 = g.add_vertex();

    auto order = graph::topological_sort(g);

    REQUIRE(order.size() == 1);
    REQUIRE(order[0] == v0);
}

TEST_CASE("Topological sort with cycle returns incomplete order") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);
    g.add_edge(v2, v0); // cycle

    auto order = graph::topological_sort(g);

    // cycle prevents a complete ordering
    REQUIRE(order.size() < g.size());
}