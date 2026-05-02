#include "graph/weighted_directed_graph.hpp"

#include <stdexcept>

// ===== Vertex iterator =====

WeightedDirectedGraph::vertex_iterator::vertex_iterator(Vertex current)
    : current_(current) {}

WeightedDirectedGraph::vertex_iterator::reference
WeightedDirectedGraph::vertex_iterator::operator*() const {
    return current_;
}

WeightedDirectedGraph::vertex_iterator&
WeightedDirectedGraph::vertex_iterator::operator++() {
    ++current_;
    return *this;
}

WeightedDirectedGraph::vertex_iterator
WeightedDirectedGraph::vertex_iterator::operator++(int) {
    vertex_iterator temp = *this;
    ++(*this);
    return temp;
}

bool WeightedDirectedGraph::vertex_iterator::operator==(
    const vertex_iterator& other
) const {
    return current_ == other.current_;
}

bool WeightedDirectedGraph::vertex_iterator::operator!=(
    const vertex_iterator& other
) const {
    return !(*this == other);
}

// ===== Graph modification =====

WeightedDirectedGraph::Vertex
WeightedDirectedGraph::add_vertex(const std::string& name) {
    adjacency_list_.emplace_back();
    vertex_properties_.push_back(VertexProperty{name});
    return adjacency_list_.size() - 1;
}

void WeightedDirectedGraph::add_edge(
    Vertex from,
    Vertex to,
    Weight weight,
    const std::string& label
) {
    check_vertex(from);
    check_vertex(to);

    adjacency_list_[from].push_back(Edge{to, weight, label});
    ++edge_count_;
}

void WeightedDirectedGraph::clear() {
    adjacency_list_.clear();
    vertex_properties_.clear();
    edge_count_ = 0;
}

// ===== Queries =====

bool WeightedDirectedGraph::has_vertex(Vertex v) const {
    return v < adjacency_list_.size();
}

bool WeightedDirectedGraph::has_edge(Vertex from, Vertex to) const {
    if (!has_vertex(from) || !has_vertex(to)) {
        return false;
    }

    for (const auto& edge : adjacency_list_[from]) {
        if (edge.to == to) {
            return true;
        }
    }

    return false;
}

const std::vector<WeightedDirectedGraph::Edge>&
WeightedDirectedGraph::neighbors(Vertex v) const {
    check_vertex(v);
    return adjacency_list_[v];
}

const WeightedDirectedGraph::VertexProperty&
WeightedDirectedGraph::vertex_property(Vertex v) const {
    check_vertex(v);
    return vertex_properties_[v];
}

WeightedDirectedGraph::size_type
WeightedDirectedGraph::size() const {
    return vertex_count();
}

WeightedDirectedGraph::size_type
WeightedDirectedGraph::vertex_count() const {
    return adjacency_list_.size();
}

WeightedDirectedGraph::size_type
WeightedDirectedGraph::edge_count() const {
    return edge_count_;
}

bool WeightedDirectedGraph::empty() const {
    return adjacency_list_.empty();
}

WeightedDirectedGraph::size_type
WeightedDirectedGraph::degree(Vertex v) const {
    check_vertex(v);
    return adjacency_list_[v].size();
}

std::vector<WeightedDirectedGraph::Vertex>
WeightedDirectedGraph::vertices() const {
    std::vector<Vertex> result;
    result.reserve(vertex_count());

    for (Vertex v = 0; v < vertex_count(); ++v) {
        result.push_back(v);
    }

    return result;
}

// ===== Iterators =====

WeightedDirectedGraph::vertex_iterator
WeightedDirectedGraph::begin() const {
    return vertex_iterator{0};
}

WeightedDirectedGraph::vertex_iterator
WeightedDirectedGraph::end() const {
    return vertex_iterator{vertex_count()};
}

WeightedDirectedGraph::vertex_iterator
WeightedDirectedGraph::cbegin() const {
    return begin();
}

WeightedDirectedGraph::vertex_iterator
WeightedDirectedGraph::cend() const {
    return end();
}

// ===== Graphviz =====

void WeightedDirectedGraph::to_graphviz(std::ostream& os) const {
    os << "digraph G {\n";

    for (Vertex v = 0; v < vertex_count(); ++v) {
        const auto& name = vertex_properties_[v].name;

        os << "  " << v << " [label=\"";

        if (name.empty()) {
            os << v;
        } else {
            os << name;
        }

        os << "\"];\n";
    }

    for (Vertex from = 0; from < vertex_count(); ++from) {
        for (const auto& edge : adjacency_list_[from]) {
            os << "  " << from << " -> " << edge.to << " [label=\"";

            if (!edge.label.empty()) {
                os << edge.label << ", ";
            }

            os << edge.weight << "\"];\n";
        }
    }

    os << "}\n";
}

// ===== Private helpers =====

void WeightedDirectedGraph::check_vertex(Vertex v) const {
    if (!has_vertex(v)) {
        throw std::out_of_range("Invalid vertex.");
    }
}