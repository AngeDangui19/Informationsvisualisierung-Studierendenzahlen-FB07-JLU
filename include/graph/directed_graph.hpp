#pragma once

#include <cstddef>
#include <vector>

class DirectedGraph {
public:
    using Vertex = std::size_t;

    DirectedGraph() = default;

    Vertex add_vertex();
    void add_edge(Vertex from, Vertex to);

    [[nodiscard]] const std::vector<Vertex>& neighbors(Vertex v) const;
    [[nodiscard]] std::size_t vertex_count() const;
    [[nodiscard]] std::size_t edge_count() const;
    [[nodiscard]] bool empty() const;

private:
    std::vector<std::vector<Vertex>> adjacency_list_{};
    std::size_t edge_count_{0};
};