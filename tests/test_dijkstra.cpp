#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "graph/weighted_directed_graph.hpp"
#include "graph/algorithms/shortest_path.hpp"

TEST_CASE("Dijkstra computes shortest distances", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex("v0");
    auto v1 = g.add_vertex("v1");
    auto v2 = g.add_vertex("v2");
    auto v3 = g.add_vertex("v3");

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto result = graph::dijkstra(g, v0);
    const auto& distances = result.distances;

    REQUIRE(distances.size() == 4);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(3.0));
    REQUIRE(distances[2] == Catch::Approx(1.0));
    REQUIRE(distances[3] == Catch::Approx(4.0));
}

TEST_CASE("Dijkstra reconstructs shortest paths", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex("v0");
    auto v1 = g.add_vertex("v1");
    auto v2 = g.add_vertex("v2");
    auto v3 = g.add_vertex("v3");

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto result = graph::dijkstra(g, v0);

    const auto path_to_v3 =
        graph::reconstruct_path<WeightedDirectedGraph>(v3, result.parents);

    REQUIRE(path_to_v3.size() == 4);
    REQUIRE(path_to_v3[0] == v0);
    REQUIRE(path_to_v3[1] == v2);
    REQUIRE(path_to_v3[2] == v1);
    REQUIRE(path_to_v3[3] == v3);
}