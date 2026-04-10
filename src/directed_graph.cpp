#include "graph/directed_graph.hpp"

DirectedGraph::Vertex DirectedGraph::add_vertex() {
    adjacency_list_.emplace_back();
    return adjacency_list_.size() - 1;
}

void DirectedGraph::add_edge(Vertex from, Vertex to) {
    adjacency_list_.at(from).push_back(to);
    ++edge_count_;
}

const std::vector<DirectedGraph::Vertex>& DirectedGraph::neighbors(Vertex v) const {
    return adjacency_list_.at(v);
}

std::size_t DirectedGraph::vertex_count() const {
    return adjacency_list_.size();
}

std::size_t DirectedGraph::edge_count() const {
    return edge_count_;
}

bool DirectedGraph::empty() const {
    return adjacency_list_.empty();
}