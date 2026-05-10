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

bool UndirectedGraph::has_edge(vertex_type a, vertex_type b) const {
    if (!has_vertex(a)) return false;
    for (auto u : adj_[a])
        if (u == b) return true;
    return false;
}

const std::vector<UndirectedGraph::vertex_type>&
UndirectedGraph::neighbors(vertex_type v) const {
    if (!has_vertex(v))
        throw std::out_of_range("Invalid vertex");
    return adj_[v];
}

std::vector<std::pair<UndirectedGraph::vertex_type, UndirectedGraph::vertex_type>>
UndirectedGraph::edges() const {
    std::vector<std::pair<vertex_type, vertex_type>> result;
    for (vertex_type a = 0; a < adj_.size(); ++a)
        for (auto b : adj_[a])
            if (a < b)
                result.emplace_back(a, b);
    return result;
}

std::size_t UndirectedGraph::size() const {
    return adj_.size();
}

std::size_t UndirectedGraph::edge_count() const {
    std::size_t count = 0;
    for (const auto& neighbors : adj_)
        count += neighbors.size();
    return count / 2;
}

std::size_t UndirectedGraph::degree(vertex_type v) const {
    if (!has_vertex(v))
        throw std::out_of_range("Invalid vertex");
    return adj_[v].size();
}

bool UndirectedGraph::empty() const {
    return adj_.empty();
}

std::vector<UndirectedGraph::vertex_type>
UndirectedGraph::vertices() const {
    std::vector<vertex_type> v;
    for (vertex_type i = 0; i < size(); ++i)
        v.push_back(i);
    return v;
}

void UndirectedGraph::to_graphviz(std::ostream& os) const {
    os << "graph {\n";
    for (vertex_type a = 0; a < adj_.size(); ++a)
        for (auto b : adj_[a])
            if (a < b)
                os << "  " << a << " -- " << b << ";\n";
    os << "}\n";
}