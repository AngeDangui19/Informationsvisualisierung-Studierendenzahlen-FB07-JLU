#include <catch2/catch_all.hpp>

#include <limits>
#include <random>
#include <stdexcept>
#include <vector>

#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

TEST_CASE("Bellman-Ford computes correct shortest distances on a simple positive graph", "[bellman_ford]")
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

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 4);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(3.0));
    REQUIRE(distances[2] == Catch::Approx(1.0));
    REQUIRE(distances[3] == Catch::Approx(4.0));
}

TEST_CASE("Bellman-Ford handles negative edge weights correctly", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, -2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 4);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(-1.0));
    REQUIRE(distances[2] == Catch::Approx(1.0));
    REQUIRE(distances[3] == Catch::Approx(0.0));
}

TEST_CASE("Bellman-Ford handles unreachable vertices", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1, 2.0);
    // v2 is unreachable from v0

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(2.0));
    REQUIRE(distances[2] == std::numeric_limits<double>::infinity());
}

TEST_CASE("Bellman-Ford works on a graph with a single vertex", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 1);
    REQUIRE(distances[0] == Catch::Approx(0.0));
}

TEST_CASE("Bellman-Ford handles a graph without edges", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == std::numeric_limits<double>::infinity());
    REQUIRE(distances[2] == std::numeric_limits<double>::infinity());
}

TEST_CASE("Bellman-Ford chooses the shorter indirect path", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1, 10.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(3.0));
    REQUIRE(distances[2] == Catch::Approx(1.0));
}

TEST_CASE("Bellman-Ford computes correct distances from another source", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, -2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto distances = bellman_ford(g, v2);

    REQUIRE(distances.size() == 4);
    REQUIRE(distances[0] == std::numeric_limits<double>::infinity());
    REQUIRE(distances[1] == Catch::Approx(-2.0));
    REQUIRE(distances[2] == Catch::Approx(0.0));
    REQUIRE(distances[3] == Catch::Approx(-1.0));
}

TEST_CASE("Bellman-Ford detects a negative-weight cycle", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1, 1.0);
    g.add_edge(v1, v2, -2.0);
    g.add_edge(v2, v1, -2.0); // negative cycle between 1 and 2

    REQUIRE_THROWS_AS(bellman_ford(g, v0), std::runtime_error);
}

TEST_CASE("Bellman-Ford handles zero-weight edges", "[bellman_ford]")
{
    WeightedDirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();

    g.add_edge(v0, v1, 0.0);
    g.add_edge(v1, v2, 0.0);

    const auto distances = bellman_ford(g, v0);

    REQUIRE(distances.size() == 3);
    REQUIRE(distances[0] == Catch::Approx(0.0));
    REQUIRE(distances[1] == Catch::Approx(0.0));
    REQUIRE(distances[2] == Catch::Approx(0.0));
}

// Bonus: randomized test with small positive and negative weights,
// but without introducing self-loops. This checks basic invariants only.
TEST_CASE("Bellman-Ford random graph basic invariants", "[bellman_ford][random]")
{
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> weight_dist(-3, 8);
    std::bernoulli_distribution edge_dist(0.30);

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

    try {
        const auto distances = bellman_ford(g, 0);

        REQUIRE(distances.size() == n);
        REQUIRE(distances[0] == Catch::Approx(0.0));

        for (double d : distances) {
            REQUIRE((d == std::numeric_limits<double>::infinity() || std::isfinite(d)));
        }
    }
    catch (const std::runtime_error&) {
        SUCCEED("Negative-weight cycle detected in randomized graph, which is a valid outcome.");
    }
}