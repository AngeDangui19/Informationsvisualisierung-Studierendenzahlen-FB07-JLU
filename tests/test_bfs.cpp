#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

TEST(BFSTest, BasicUndirectedGraph) {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    const auto result = bfs(graph, 0);

    EXPECT_FALSE(result.empty());
}