#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

TEST(BellmanFordTest, SimpleWeightedDirectedGraph) {
    WeightedDirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1, 2.0);

    const auto distances = bellman_ford(graph, 0);

    EXPECT_FALSE(distances.empty());
    EXPECT_EQ(distances.size(), graph.vertex_count());
}