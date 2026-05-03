#pragma once

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

namespace graph {

// Directed graph
bool is_dag(const DirectedGraph& graph);

// Undirected graph
bool is_tree(const UndirectedGraph& graph);

// Weighted directed graph
bool has_only_positive_weights(const WeightedDirectedGraph& graph);

// Weighted undirected graph
bool is_connected(const WeightedUndirectedGraph& graph);

} // namespace graph