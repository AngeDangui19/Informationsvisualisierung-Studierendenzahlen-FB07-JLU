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

bool WeightedDirectedGraph::has_vertex(Vertex v) const {
    return v < adjacency_list_.size();
}

bool WeightedDirectedGraph::has_edge(Vertex from, Vertex to) const {
    for (const auto& [neighbor, weight] : adjacency_list_.at(from)) {
        (void)weight;
        if (neighbor == to) {
            return true;
        }
    }
    return false;
}

std::size_t WeightedDirectedGraph::degree(Vertex v) const {
    return adjacency_list_.at(v).size();
}

std::vector<WeightedDirectedGraph::Vertex>
WeightedDirectedGraph::vertices() const {
    std::vector<Vertex> result;
    result.reserve(adjacency_list_.size());

    for (Vertex v = 0; v < adjacency_list_.size(); ++v) {
        result.push_back(v);
    }

    return result;
}