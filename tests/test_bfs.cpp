#include <catch2/catch_test_macros.hpp>
#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/algorithms/traversal.hpp"

TEST_CASE("BFS starts from the correct vertex") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v0, v2);

    auto order = graph::bfs(g, v0);

    REQUIRE(order[0] == v0);
    REQUIRE(order.size() == 3);
}

TEST_CASE("BFS visits level by level") {
    DirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v0, v2);
    g.add_edge(v1, v3);

    auto order = graph::bfs(g, v0);

    // v0 first, then its direct neighbors v1 and v2, then v3
    REQUIRE(order[0] == v0);
    REQUIRE(order.size() == 4);
    // v3 must come after v1 and v2
    auto pos_v1 = std::find(order.begin(), order.end(), v1) - order.begin();
    auto pos_v2 = std::find(order.begin(), order.end(), v2) - order.begin();
    auto pos_v3 = std::find(order.begin(), order.end(), v3) - order.begin();
    REQUIRE(pos_v3 > pos_v1);
    REQUIRE(pos_v3 > pos_v2);
}

TEST_CASE("BFS on single vertex") {
    DirectedGraph g;
    auto v0 = g.add_vertex();

    auto order = graph::bfs(g, v0);

    REQUIRE(order.size() == 1);
    REQUIRE(order[0] == v0);
}

TEST_CASE("BFS does not revisit vertices in a cycle") {
    UndirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);
    g.add_edge(v2, v0); // cycle

    auto order = graph::bfs(g, v0);

    REQUIRE(order.size() == 3);
}

TEST_CASE("BFS does not reach disconnected vertices") {
    UndirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex(); // isolated

    g.add_edge(v0, v1);

    auto order = graph::bfs(g, v0);

    REQUIRE(order.size() == 2);
    REQUIRE(std::find(order.begin(), order.end(), v2) == order.end());
}