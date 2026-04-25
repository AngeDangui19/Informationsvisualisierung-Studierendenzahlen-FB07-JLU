#include "graph/weighted_undirected_graph.hpp"

WeightedUndirectedGraph::Vertex WeightedUndirectedGraph::add_vertex() {
    adjacency_list_.emplace_back();
    return adjacency_list_.size() - 1;
}

void WeightedUndirectedGraph::add_edge(Vertex u, Vertex v, Weight weight) {
    adjacency_list_[u].push_back({u, v, weight});
    adjacency_list_[v].push_back({v, u, weight});
    ++edge_count_;
}

const std::vector<WeightedUndirectedGraph::Edge>&
WeightedUndirectedGraph::neighbors(Vertex v) const {
    return adjacency_list_[v];
}

std::vector<WeightedUndirectedGraph::Edge>
WeightedUndirectedGraph::edges() const {
    std::vector<Edge> result;

    for (Vertex u = 0; u < adjacency_list_.size(); ++u) {
        for (const auto& edge : adjacency_list_[u]) {
            if (edge.from < edge.to) {
                result.push_back(edge);
            }
        }
    }

    return result;
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

bool WeightedUndirectedGraph::has_vertex(Vertex v) const {
    return v < adjacency_list_.size();
}

bool WeightedUndirectedGraph::has_edge(Vertex u, Vertex v) const {
    for (const auto& edge : adjacency_list_[u]) {
        if (edge.to == v) {
            return true;
        }
    }
    return false;
}

std::size_t WeightedUndirectedGraph::degree(Vertex v) const {
    return adjacency_list_[v].size();
}

std::vector<WeightedUndirectedGraph::Vertex>
WeightedUndirectedGraph::vertices() const {
    std::vector<Vertex> result;
    result.reserve(adjacency_list_.size());

    for (Vertex v = 0; v < adjacency_list_.size(); ++v) {
        result.push_back(v);
    }

    return result;
}