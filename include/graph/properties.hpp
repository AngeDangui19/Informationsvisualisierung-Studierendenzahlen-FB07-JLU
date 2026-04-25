#pragma once

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

namespace graph {

bool is_dag(const DirectedGraph& graph);

bool is_tree(const UndirectedGraph& graph);

bool has_only_positive_weights(const WeightedDirectedGraph& graph);

bool is_connected(const WeightedUndirectedGraph& graph);

} // namespace graph