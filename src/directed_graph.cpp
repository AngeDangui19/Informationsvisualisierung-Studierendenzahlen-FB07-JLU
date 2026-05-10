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

bool DirectedGraph::has_edge(vertex_type from, vertex_type to) const {
    if (!has_vertex(from)) return false;
    for (auto u : adj_[from])
        if (u == to) return true;
    return false;
}

const std::vector<DirectedGraph::vertex_type>&
DirectedGraph::neighbors(vertex_type v) const {
    if (!has_vertex(v))
        throw std::out_of_range("Invalid vertex");
    return adj_[v];
}

std::vector<std::pair<DirectedGraph::vertex_type, DirectedGraph::vertex_type>>
DirectedGraph::edges() const {
    std::vector<std::pair<vertex_type, vertex_type>> result;
    for (vertex_type from = 0; from < adj_.size(); ++from)
        for (auto to : adj_[from])
            result.emplace_back(from, to);
    return result;
}

std::size_t DirectedGraph::size() const {
    return adj_.size();
}

std::size_t DirectedGraph::edge_count() const {
    std::size_t count = 0;
    for (const auto& neighbors : adj_)
        count += neighbors.size();
    return count;
}

std::size_t DirectedGraph::degree(vertex_type v) const {
    if (!has_vertex(v))
        throw std::out_of_range("Invalid vertex");
    return adj_[v].size();
}

std::size_t DirectedGraph::in_degree(vertex_type v) const {
    if (!has_vertex(v))
        throw std::out_of_range("Invalid vertex");
    std::size_t count = 0;
    for (const auto& neighbors : adj_)
        for (auto u : neighbors)
            if (u == v) ++count;
    return count;
}

bool DirectedGraph::empty() const {
    return adj_.empty();
}

std::vector<DirectedGraph::vertex_type>
DirectedGraph::vertices() const {
    std::vector<vertex_type> v;
    for (vertex_type i = 0; i < size(); ++i)
        v.push_back(i);
    return v;
}

void DirectedGraph::to_graphviz(std::ostream& os) const {
    os << "digraph {\n";
    for (vertex_type from = 0; from < adj_.size(); ++from)
        for (auto to : adj_[from])
            os << "  " << from << " -> " << to << ";\n";
    os << "}\n";
}