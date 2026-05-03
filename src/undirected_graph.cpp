#include "graph/undirected_graph.hpp"

UndirectedGraph::vertex_type UndirectedGraph::add_vertex() {
    adj_.emplace_back();
    return adj_.size() - 1;
}

void UndirectedGraph::add_edge(vertex_type a, vertex_type b) {
    if (!has_vertex(a) || !has_vertex(b))
        throw std::out_of_range("Invalid vertex");

    adj_[a].push_back(b);
    adj_[b].push_back(a);
}

bool UndirectedGraph::has_vertex(vertex_type v) const {
    return v < adj_.size();
}

const std::vector<UndirectedGraph::vertex_type>&
UndirectedGraph::neighbors(vertex_type v) const {
    return adj_[v];
}

std::size_t UndirectedGraph::size() const {
    return adj_.size();
}

std::vector<UndirectedGraph::vertex_type>
UndirectedGraph::vertices() const {
    std::vector<vertex_type> v;
    for (vertex_type i = 0; i < size(); ++i)
        v.push_back(i);
    return v;
}