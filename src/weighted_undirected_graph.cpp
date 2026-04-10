#include "graph/weighted_undirected_graph.hpp"

WeightedUndirectedGraph::Vertex WeightedUndirectedGraph::add_vertex() {
    adjacency_list_.emplace_back();
    return adjacency_list_.size() - 1;
}

void WeightedUndirectedGraph::add_edge(Vertex u, Vertex v, Weight weight) {
    adjacency_list_.at(u).push_back({v, weight});
    adjacency_list_.at(v).push_back({u, weight});
    ++edge_count_;
}

const std::vector<WeightedUndirectedGraph::Edge>& WeightedUndirectedGraph::neighbors(Vertex v) const {
    return adjacency_list_.at(v);
}

std::size_t WeightedUndirectedGraph::vertex_count() const {
    return adjacency_list_.size();
}

std::size_t WeightedUndirectedGraph::edge_count() const {
    return edge_count_;
}

bool WeightedUndirectedGraph::empty() const {
    return adjacency_list_.empty();
}