#include <catch2/catch_test_macros.hpp>
#include "graph/undirected_graph.hpp"
#include "graph/algorithms/connectivity.hpp"

TEST_CASE("Two distinct connected components") {
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

TEST_CASE("Fully connected graph has one component") {
    UndirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v1, v2);

    REQUIRE(graph::count_components(g) == 1);
    REQUIRE(graph::is_connected(g) == true);
}

TEST_CASE("Isolated vertices each form their own component") {
    UndirectedGraph g;
    g.add_vertex(); // 0
    g.add_vertex(); // 1
    g.add_vertex(); // 2

    REQUIRE(graph::count_components(g) == 3);
    REQUIRE(graph::is_connected(g) == false);
}

TEST_CASE("Component IDs are correctly assigned") {
    UndirectedGraph g;
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1);
    g.add_edge(v2, v3);

    auto ids = graph::component_ids(g);

    // v0 and v1 share the same component
    REQUIRE(ids[v0] == ids[v1]);
    // v2 and v3 share the same component
    REQUIRE(ids[v2] == ids[v3]);
    // but the two groups are different
    REQUIRE(ids[v0] != ids[v2]);
}

TEST_CASE("Single vertex graph is connected") {
    UndirectedGraph g;
    g.add_vertex();

    REQUIRE(graph::is_connected(g) == true);
    REQUIRE(graph::count_components(g) == 1);
}