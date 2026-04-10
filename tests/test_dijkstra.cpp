#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

TEST(DijkstraTest, SimpleWeightedDirectedGraph) {
    WeightedDirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1, 3.0);

    const auto distances = dijkstra(graph, 0);

    EXPECT_FALSE(distances.empty());
}