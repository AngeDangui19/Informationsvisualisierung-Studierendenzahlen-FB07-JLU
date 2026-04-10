#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

TEST(DFSTest, BasicUndirectedGraph) {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    const auto result = dfs(graph, 0);

    EXPECT_FALSE(result.empty());
}