#include <gtest/gtest.h>

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

TEST(DirectedGraphTest, AddVertex) {
    DirectedGraph graph;
    auto v = graph.add_vertex();
    EXPECT_EQ(v, 0);
    EXPECT_EQ(graph.vertex_count(), 1);
}

TEST(UndirectedGraphTest, AddEdge) {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_edge(0, 1);

    EXPECT_EQ(graph.edge_count(), 1);
    EXPECT_EQ(graph.neighbors(0).size(), 1);
    EXPECT_EQ(graph.neighbors(1).size(), 1);
}