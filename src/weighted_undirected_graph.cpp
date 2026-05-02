#include "graph/weighted_undirected_graph.hpp"

#include <stdexcept>

WeightedUndirectedGraph::vertex_iterator::vertex_iterator(Vertex current)
    : current_(current) {}

WeightedUndirectedGraph::vertex_iterator::reference
WeightedUndirectedGraph::vertex_iterator::operator*() const {
    return current_;
}

WeightedUndirectedGraph::vertex_iterator&
WeightedUndirectedGraph::vertex_iterator::operator++() {
    ++current_;
    return *this;
}

WeightedUndirectedGraph::vertex_iterator
WeightedUndirectedGraph::vertex_iterator::operator++(int) {
    vertex_iterator temp = *this;
    ++(*this);
    return temp;
}

bool WeightedUndirectedGraph::vertex_iterator::operator==(
    const vertex_iterator& other
) const {
    return current_ == other.current_;
}

bool WeightedUndirectedGraph::vertex_iterator::operator!=(
    const vertex_iterator& other
) const {
    return !(*this == other);
}

WeightedUndirectedGraph::Vertex
WeightedUndirectedGraph::add_vertex(const std::string& name) {
    adjacency_list_.emplace_back();
    vertex_properties_.push_back(VertexProperty{name});
    return adjacency_list_.size() - 1;
}

void WeightedUndirectedGraph::add_edge(
    Vertex a,
    Vertex b,
    Weight weight,
    const std::string& label
) {
    check_vertex(a);
    check_vertex(b);

    adjacency_list_[a].push_back(Edge{b, weight, label});

    if (a != b) {
        adjacency_list_[b].push_back(Edge{a, weight, label});
    }

    ++edge_count_;
}

void WeightedUndirectedGraph::clear() {
    adjacency_list_.clear();
    vertex_properties_.clear();
    edge_count_ = 0;
}

bool WeightedUndirectedGraph::has_vertex(Vertex v) const {
    return v < adjacency_list_.size();
}

bool WeightedUndirectedGraph::has_edge(Vertex a, Vertex b) const {
    if (!has_vertex(a) || !has_vertex(b)) {
        return false;
    }

    for (const auto& edge : adjacency_list_[a]) {
        if (edge.to == b) {
            return true;
        }
    }

    return false;
}

const std::vector<WeightedUndirectedGraph::Edge>&
WeightedUndirectedGraph::neighbors(Vertex v) const {
    check_vertex(v);
    return adjacency_list_[v];
}

const WeightedUndirectedGraph::VertexProperty&
WeightedUndirectedGraph::vertex_property(Vertex v) const {
    check_vertex(v);
    return vertex_properties_[v];
}

WeightedUndirectedGraph::size_type
WeightedUndirectedGraph::size() const {
    return vertex_count();
}

WeightedUndirectedGraph::size_type
WeightedUndirectedGraph::vertex_count() const {
    return adjacency_list_.size();
}

WeightedUndirectedGraph::size_type
WeightedUndirectedGraph::edge_count() const {
    return edge_count_;
}

bool WeightedUndirectedGraph::empty() const {
    return adjacency_list_.empty();
}

WeightedUndirectedGraph::size_type
WeightedUndirectedGraph::degree(Vertex v) const {
    check_vertex(v);
    return adjacency_list_[v].size();
}

std::vector<WeightedUndirectedGraph::Vertex>
WeightedUndirectedGraph::vertices() const {
    std::vector<Vertex> result;
    result.reserve(vertex_count());

    for (Vertex v = 0; v < vertex_count(); ++v) {
        result.push_back(v);
    }

    return result;
}

WeightedUndirectedGraph::vertex_iterator
WeightedUndirectedGraph::begin() const {
    return vertex_iterator{0};
}

WeightedUndirectedGraph::vertex_iterator
WeightedUndirectedGraph::end() const {
    return vertex_iterator{vertex_count()};
}

WeightedUndirectedGraph::vertex_iterator
WeightedUndirectedGraph::cbegin() const {
    return begin();
}

WeightedUndirectedGraph::vertex_iterator
WeightedUndirectedGraph::cend() const {
    return end();
}

void WeightedUndirectedGraph::to_graphviz(std::ostream& os) const {
    os << "graph G {\n";

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
            if (from <= edge.to) {
                os << "  " << from << " -- " << edge.to << " [label=\"";

                if (!edge.label.empty()) {
                    os << edge.label << ", ";
                }

                os << edge.weight << "\"];\n";
            }
        }
    }

    os << "}\n";
}

void WeightedUndirectedGraph::check_vertex(Vertex v) const {
    if (!has_vertex(v)) {
        throw std::out_of_range("Invalid vertex.");
    }
}