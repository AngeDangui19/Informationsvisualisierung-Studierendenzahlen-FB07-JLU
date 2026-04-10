#pragma once

#include <vector>

#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/weighted_directed_graph.hpp"
#include "graph/weighted_undirected_graph.hpp"

// Traversal algorithms
std::vector<DirectedGraph::Vertex> bfs(const DirectedGraph& graph, DirectedGraph::Vertex start);
std::vector<UndirectedGraph::Vertex> bfs(const UndirectedGraph& graph, UndirectedGraph::Vertex start);

std::vector<DirectedGraph::Vertex> dfs(const DirectedGraph& graph, DirectedGraph::Vertex start);
std::vector<UndirectedGraph::Vertex> dfs(const UndirectedGraph& graph, UndirectedGraph::Vertex start);

std::vector<DirectedGraph::Vertex> topological_sort(const DirectedGraph& graph);

// Shortest path algorithms
std::vector<double> dijkstra(const WeightedDirectedGraph& graph, WeightedDirectedGraph::Vertex start);
std::vector<double> dijkstra(const WeightedUndirectedGraph& graph, WeightedUndirectedGraph::Vertex start);

// Optional
std::vector<double> bellman_ford(const WeightedDirectedGraph& graph, WeightedDirectedGraph::Vertex start);

// MST algorithms
WeightedUndirectedGraph prim(const WeightedUndirectedGraph& graph, WeightedUndirectedGraph::Vertex start);
WeightedUndirectedGraph kruskal(const WeightedUndirectedGraph& graph);

// Connectivity algorithms
std::vector<std::vector<UndirectedGraph::Vertex>> connected_components(const UndirectedGraph& graph);