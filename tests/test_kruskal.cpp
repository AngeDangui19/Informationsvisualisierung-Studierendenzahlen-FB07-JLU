#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/weighted_undirected_graph.hpp"

TEST(KruskalTest, SimpleWeightedUndirectedGraph) {
    WeightedUndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1, 1.0);

    const auto mst = kruskal(graph);

    EXPECT_LE(mst.edge_count(), graph.edge_count());
}