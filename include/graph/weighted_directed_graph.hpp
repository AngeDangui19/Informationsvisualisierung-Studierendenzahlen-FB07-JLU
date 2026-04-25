#pragma once

#include <cstddef>
#include <utility>
#include <vector>

class WeightedDirectedGraph {
public:
    using Vertex = std::size_t;
    using Weight = double;
    using Edge = std::pair<Vertex, Weight>;

    WeightedDirectedGraph() = default;

    Vertex add_vertex();
    void add_edge(Vertex from, Vertex to, Weight weight);

    [[nodiscard]] const std::vector<Edge>& neighbors(Vertex v) const;
    [[nodiscard]] std::size_t vertex_count() const;
    [[nodiscard]] std::size_t edge_count() const;
    [[nodiscard]] bool empty() const;

    [[nodiscard]] bool has_vertex(Vertex v) const;
    [[nodiscard]] bool has_edge(Vertex from, Vertex to) const;
    [[nodiscard]] std::size_t degree(Vertex v) const;
    [[nodiscard]] std::vector<Vertex> vertices() const;

private:
    std::vector<std::vector<Edge>> adjacency_list_{};
    std::size_t edge_count_{0};
};