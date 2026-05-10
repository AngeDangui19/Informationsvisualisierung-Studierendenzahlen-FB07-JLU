#include <catch2/catch_test_macros.hpp>
#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/algorithms/traversal.hpp"

TEST_CASE("DFS starts from the correct vertex") {
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

TEST_CASE("DFS visits all reachable vertices") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();
    auto v4 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v0, v2);
    g.add_edge(v1, v3);
    g.add_edge(v1, v4);

    auto order = graph::dfs(g, v0);

    REQUIRE(order.size() == 5);
    REQUIRE(order[0] == v0);
}

TEST_CASE("DFS on single vertex") {
    DirectedGraph g;
    auto v0 = g.add_vertex();

    auto order = graph::dfs(g, v0);

    REQUIRE(order.size() == 1);
    REQUIRE(order[0] == v0);
}

TEST_CASE("DFS does not revisit vertices in a cycle") {
    UndirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);
    g.add_edge(v2, v3);
    g.add_edge(v3, v0); // cycle

    auto order = graph::dfs(g, v0);

    REQUIRE(order.size() == 4);
}

TEST_CASE("DFS does not reach disconnected vertices") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex(); // isolated

    g.add_edge(v0, v1);

    auto order = graph::dfs(g, v0);

    REQUIRE(order.size() == 2);
    REQUIRE(std::find(order.begin(), order.end(), v2) == order.end());
}