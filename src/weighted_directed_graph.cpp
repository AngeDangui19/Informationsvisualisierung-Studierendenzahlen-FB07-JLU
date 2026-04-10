#include "graph/weighted_directed_graph.hpp"

WeightedDirectedGraph::Vertex WeightedDirectedGraph::add_vertex() {
    adjacency_list_.emplace_back();
    return adjacency_list_.size() - 1;
}

void WeightedDirectedGraph::add_edge(Vertex from, Vertex to, Weight weight) {
    adjacency_list_.at(from).push_back({to, weight});
    ++edge_count_;
}

const std::vector<WeightedDirectedGraph::Edge>& WeightedDirectedGraph::neighbors(Vertex v) const {
    return adjacency_list_.at(v);
}

std::size_t WeightedDirectedGraph::vertex_count() const {
    return adjacency_list_.size();
}

std::size_t WeightedDirectedGraph::edge_count() const {
    return edge_count_;
}

bool WeightedDirectedGraph::empty() const {
    return adjacency_list_.empty();
}