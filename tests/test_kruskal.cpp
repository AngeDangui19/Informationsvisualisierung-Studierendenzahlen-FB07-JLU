#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <algorithm>
#include <random>
#include <tuple>
#include <vector>

#include "graph/weighted_undirected_graph.hpp"
#include "graph/algorithms/mst.hpp"

namespace {

using MSTEdge = std::tuple<
    WeightedUndirectedGraph::vertex_type,
    WeightedUndirectedGraph::vertex_type,
    WeightedUndirectedGraph::weight_type
>;

double total_weight(const std::vector<MSTEdge>& edges) {
    double total = 0.0;

    for (const auto& edge : edges) {
        total += std::get<2>(edge);
    }

    return total;
}

bool contains_edge(
    const std::vector<MSTEdge>& edges,
    std::size_t u,
    std::size_t v,
    double weight
) {
    return std::any_of(edges.begin(), edges.end(), [=](const auto& edge) {
        auto from = std::get<0>(edge);
        auto to = std::get<1>(edge);
        auto w = std::get<2>(edge);

        return ((from == u && to == v) || (from == v && to == u)) &&
               w == Catch::Approx(weight);
    });
}

} // namespace

TEST_CASE("Kruskal computes correct MST on simple graph", "[kruskal]") {
    WeightedUndirectedGraph g;

    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v1, v2, -2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == 3);
    REQUIRE(total_weight(mst) == Catch::Approx(0.0));

    REQUIRE(contains_edge(mst, 1, 2, -2.0));
    REQUIRE(contains_edge(mst, 0, 2, 1.0));
    REQUIRE(contains_edge(mst, 1, 3, 1.0));
}

TEST_CASE("Kruskal works on an empty graph", "[kruskal]") {
    WeightedUndirectedGraph g;

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.empty());
}

TEST_CASE("Kruskal works on a graph with a single vertex", "[kruskal]") {
    WeightedUndirectedGraph g;
    g.add_vertex();

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.empty());
}

TEST_CASE("Kruskal handles a graph without edges", "[kruskal]") {
    WeightedUndirectedGraph g;

    g.add_vertex();
    g.add_vertex();
    g.add_vertex();

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.empty());
}

TEST_CASE("Kruskal keeps all edges if the graph is already a tree", "[kruskal]") {
    WeightedUndirectedGraph g;

    for (int i = 0; i < 4; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 2.0);
    g.add_edge(2, 3, 3.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == 3);
    REQUIRE(total_weight(mst) == Catch::Approx(6.0));
}

TEST_CASE("Kruskal chooses lighter edges and avoids cycles", "[kruskal]") {
    WeightedUndirectedGraph g;

    for (int i = 0; i < 3; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1, 10.0);
    g.add_edge(0, 2, 1.0);
    g.add_edge(1, 2, 2.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == 2);
    REQUIRE(total_weight(mst) == Catch::Approx(3.0));
    REQUIRE(contains_edge(mst, 0, 2, 1.0));
    REQUIRE(contains_edge(mst, 1, 2, 2.0));
}

TEST_CASE("Kruskal handles negative edge weights", "[kruskal]") {
    WeightedUndirectedGraph g;

    for (int i = 0; i < 4; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1, -5.0);
    g.add_edge(1, 2, -2.0);
    g.add_edge(2, 3, 3.0);
    g.add_edge(0, 3, 10.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == 3);
    REQUIRE(total_weight(mst) == Catch::Approx(-4.0));
}

TEST_CASE("Kruskal handles equal edge weights", "[kruskal]") {
    WeightedUndirectedGraph g;

    for (int i = 0; i < 4; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 1.0);
    g.add_edge(2, 3, 1.0);
    g.add_edge(3, 0, 1.0);
    g.add_edge(0, 2, 1.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == 3);
    REQUIRE(total_weight(mst) == Catch::Approx(3.0));
}

TEST_CASE("Kruskal returns a forest for disconnected graphs", "[kruskal]") {
    WeightedUndirectedGraph g;

    for (int i = 0; i < 5; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 2.0);
    g.add_edge(3, 4, 3.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == 3);
    REQUIRE(total_weight(mst) == Catch::Approx(6.0));
}

TEST_CASE("Kruskal MST has vertex_count minus one edges for connected graph", "[kruskal]") {
    WeightedUndirectedGraph g;

    for (int i = 0; i < 5; ++i) {
        g.add_vertex();
    }

    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 2.0);
    g.add_edge(2, 3, 3.0);
    g.add_edge(3, 4, 4.0);
    g.add_edge(0, 4, 10.0);
    g.add_edge(1, 4, 5.0);

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == g.vertex_count() - 1);
    REQUIRE(total_weight(mst) == Catch::Approx(10.0));
}

TEST_CASE("Kruskal random connected graph basic invariants", "[kruskal][random]") {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> weight_dist(-5, 15);
    std::bernoulli_distribution extra_edge_dist(0.4);

    WeightedUndirectedGraph g;
    constexpr std::size_t n = 6;

    for (std::size_t i = 0; i < n; ++i) {
        g.add_vertex();
    }

    for (std::size_t i = 0; i + 1 < n; ++i) {
        g.add_edge(i, i + 1, static_cast<double>(weight_dist(gen)));
    }

    for (std::size_t u = 0; u < n; ++u) {
        for (std::size_t v = u + 2; v < n; ++v) {
            if (extra_edge_dist(gen)) {
                g.add_edge(u, v, static_cast<double>(weight_dist(gen)));
            }
        }
    }

    const auto mst = graph::kruskal(g);

    REQUIRE(mst.size() == n - 1);

    for (const auto& edge : mst) {
        REQUIRE(g.has_edge(std::get<0>(edge), std::get<1>(edge)));
    }
}