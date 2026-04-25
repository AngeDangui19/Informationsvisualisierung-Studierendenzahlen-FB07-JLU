#include <catch2/catch_all.hpp>

#include <limits>
#include <random>
#include <vector>

#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

TEST_CASE("Dijkstra computes correct shortest distances on a simple graph", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto distances = dijkstra(g, v0);

    REQUIRE(distances.size() == 4);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(3.0));
    REQUIRE(distances[2] == Catch::Approx(1.0));
    REQUIRE(distances[3] == Catch::Approx(4.0));
}

TEST_CASE("Dijkstra handles unreachable vertices", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1, 2.0);
    // v2 is unreachable from v0

    const auto distances = dijkstra(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(2.0));
    REQUIRE(distances[2] == std::numeric_limits<double>::infinity());
}

TEST_CASE("Dijkstra works on a graph with a single vertex", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();

    const auto distances = dijkstra(g, v0);

    REQUIRE(distances.size() == 1);
    REQUIRE(distances[0] == Catch::Approx(0.0));
}

TEST_CASE("Dijkstra handles a graph without edges", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    const auto distances = dijkstra(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == std::numeric_limits<double>::infinity());
    REQUIRE(distances[2] == std::numeric_limits<double>::infinity());
}

TEST_CASE("Dijkstra chooses the shorter indirect path", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1, 10.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);

    const auto distances = dijkstra(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(3.0));
    REQUIRE(distances[2] == Catch::Approx(1.0));
}

TEST_CASE("Dijkstra computes correct distances from another source", "[dijkstra]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto distances = dijkstra(g, v2);

    REQUIRE(distances.size() == 4);
    REQUIRE(distances[0] == std::numeric_limits<double>::infinity());
    REQUIRE(distances[1] == Catch::Approx(2.0));
    REQUIRE(distances[2] == Catch::Approx(0.0));
    REQUIRE(distances[3] == Catch::Approx(3.0));
}

// Bonus: simple randomized invariant test with positive weights only
TEST_CASE("Dijkstra random positive graph basic invariants", "[dijkstra][random]")
{
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> weight_dist(1, 10);
    std::bernoulli_distribution edge_dist(0.35);

    WeightedDirectedGraph g;
    constexpr std::size_t n = 6;

    for (std::size_t i = 0; i < n; ++i) {
        g.add_vertex();
    }

    for (std::size_t u = 0; u < n; ++u) {
        for (std::size_t v = 0; v < n; ++v) {
            if (u != v && edge_dist(gen)) {
                g.add_edge(u, v, static_cast<double>(weight_dist(gen)));
            }
        }
    }

    const auto distances = dijkstra(g, 0);

    REQUIRE(distances.size() == n);
    REQUIRE(distances[0] == Catch::Approx(0.0));

    for (double d : distances) {
        REQUIRE((d >= 0.0 || d == std::numeric_limits<double>::infinity()));
    }
}