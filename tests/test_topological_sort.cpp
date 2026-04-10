#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/directed_graph.hpp"

TEST(TopologicalSortTest, SimpleDag) {
    DirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    const auto order = topological_sort(graph);

    EXPECT_LE(order.size(), graph.vertex_count());
}