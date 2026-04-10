#include "graph/undirected_graph.hpp"

UndirectedGraph::Vertex UndirectedGraph::add_vertex() {
    adjacency_list_.emplace_back();
    return adjacency_list_.size() - 1;
}

void UndirectedGraph::add_edge(Vertex u, Vertex v) {
    adjacency_list_.at(u).push_back(v);
    adjacency_list_.at(v).push_back(u);
    ++edge_count_;
}

const std::vector<UndirectedGraph::Vertex>& UndirectedGraph::neighbors(Vertex v) const {
    return adjacency_list_.at(v);
}

std::size_t UndirectedGraph::vertex_count() const {
    return adjacency_list_.size();
}

std::size_t UndirectedGraph::edge_count() const {
    return edge_count_;
}

bool UndirectedGraph::empty() const {
    return adjacency_list_.empty();
}