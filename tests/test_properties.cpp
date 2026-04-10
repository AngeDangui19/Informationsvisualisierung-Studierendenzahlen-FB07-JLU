#include <gtest/gtest.h>

#include "graph/properties.hpp"
#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

TEST(PropertiesTest, DagProperty) {
    DirectedGraph graph;
    graph.add_vertex();
    EXPECT_FALSE(is_dag(graph)); // placeholder expectation
}

TEST(PropertiesTest, PositiveWeightsProperty) {
    WeightedDirectedGraph graph;
    graph.add_vertex();
    EXPECT_FALSE(has_only_positive_weights(graph)); // placeholder expectation
}