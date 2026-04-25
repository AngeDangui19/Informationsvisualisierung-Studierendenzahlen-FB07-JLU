#pragma once

#include <cstddef>
#include <vector>

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

namespace graph {

std::vector<std::vector<std::size_t>>
connected_components(const UndirectedGraph& graph);

std::vector<DirectedGraph::Vertex>
topological_sort(const DirectedGraph& graph);

} // namespace graph

// Shortest path algorithms
std::vector<double>
dijkstra(const WeightedDirectedGraph& graph,
         WeightedDirectedGraph::Vertex source);

std::vector<double>
bellman_ford(const WeightedDirectedGraph& graph,
             WeightedDirectedGraph::Vertex source);

// MST algorithms
std::vector<WeightedUndirectedGraph::Edge>
kruskal(const WeightedUndirectedGraph& graph);

std::vector<WeightedUndirectedGraph::Edge>
prim(const WeightedUndirectedGraph& graph,
     WeightedUndirectedGraph::Vertex start);