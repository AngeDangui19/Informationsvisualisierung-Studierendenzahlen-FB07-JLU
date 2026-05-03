#include "graph/directed_graph.hpp"

DirectedGraph::vertex_type DirectedGraph::add_vertex() {
    adj_.emplace_back();
    return adj_.size() - 1;
}

void DirectedGraph::add_edge(vertex_type from, vertex_type to) {
    if (!has_vertex(from) || !has_vertex(to))
        throw std::out_of_range("Invalid vertex");

    adj_[from].push_back(to);
}

bool DirectedGraph::has_vertex(vertex_type v) const {
    return v < adj_.size();
}

const std::vector<DirectedGraph::vertex_type>&
DirectedGraph::neighbors(vertex_type v) const {
    return adj_[v];
}

std::size_t DirectedGraph::size() const {
    return adj_.size();
}

std::vector<DirectedGraph::vertex_type>
DirectedGraph::vertices() const {
    std::vector<vertex_type> v;
    for (vertex_type i = 0; i < size(); ++i)
        v.push_back(i);
    return v;
}