#pragma once

#include <cstddef>
#include <utility>
#include <vector>

class WeightedUndirectedGraph {
public:
    using Vertex = std::size_t;
    using Weight = double;
    struct Edge {
        Vertex from;
        Vertex to;
        Weight weight;
    };

    WeightedUndirectedGraph() = default;

    Vertex add_vertex();
    void add_edge(Vertex u, Vertex v, Weight weight);

    [[nodiscard]] const std::vector<Edge>& neighbors(Vertex v) const;
    [[nodiscard]] std::vector<Edge> edges() const;
    [[nodiscard]] std::size_t vertex_count() const;
    [[nodiscard]] std::size_t edge_count() const;
    [[nodiscard]] bool empty() const;

    [[nodiscard]] bool has_vertex(Vertex v) const;
    [[nodiscard]] bool has_edge(Vertex u, Vertex v) const;
    [[nodiscard]] std::size_t degree(Vertex v) const;
    [[nodiscard]] std::vector<Vertex> vertices() const;

private:
    std::vector<std::vector<Edge>> adjacency_list_{};
    std::size_t edge_count_{0};
};