#include <gtest/gtest.h>

#include "graph/algorithms.hpp"
#include "graph/undirected_graph.hpp"

TEST(ConnectedComponentsTest, TwoComponents) {
    UndirectedGraph graph;
    graph.add_vertex();
    graph.add_vertex();
    graph.add_vertex();
    graph.add_vertex();

    graph.add_edge(0, 1);
    graph.add_edge(2, 3);

    const auto components = connected_components(graph);

    EXPECT_FALSE(components.empty());
}