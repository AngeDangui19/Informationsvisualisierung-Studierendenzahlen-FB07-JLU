
#include <catch2/catch_test_macros.hpp>

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

TEST_CASE("DirectedGraph basic operations") {
    DirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();

    g.add_edge(v0, v1);

    REQUIRE(g.size() == 2);
    REQUIRE(g.has_vertex(v0));
    REQUIRE(g.has_vertex(v1));

    auto n = g.neighbors(v0);
    REQUIRE(n.size() == 1);
    REQUIRE(n[0] == v1);
}

TEST_CASE("UndirectedGraph basic operations") {
    UndirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();

    g.add_edge(v0, v1);

    REQUIRE(g.size() == 2);

    REQUIRE(g.neighbors(v0)[0] == v1);
    REQUIRE(g.neighbors(v1)[0] == v0);
}

TEST_CASE("WeightedDirectedGraph basic operations") {
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex("v0");
    auto v1 = g.add_vertex("v1");

    g.add_edge(v0, v1, 4.0, "e0");

    REQUIRE(g.vertex_count() == 2);
    REQUIRE(g.edge_count() == 1);

    REQUIRE(g.vertex_property(v0).name == "v0");

    auto n = g.neighbors(v0);
    REQUIRE(n[0].to == v1);
    REQUIRE(n[0].weight == 4.0);
    REQUIRE(n[0].label == "e0");
}

TEST_CASE("WeightedUndirectedGraph basic operations") {
    WeightedUndirectedGraph g;

    auto v0 = g.add_vertex("v0");
    auto v1 = g.add_vertex("v1");

    g.add_edge(v0, v1, 2.0, "e1");

    REQUIRE(g.edge_count() == 1);

    REQUIRE(g.neighbors(v0)[0].to == v1);
    REQUIRE(g.neighbors(v1)[0].to == v0);
}