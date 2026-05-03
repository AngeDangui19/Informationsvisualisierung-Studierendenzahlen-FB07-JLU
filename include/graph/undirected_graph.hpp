#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>

class UndirectedGraph {
public:
    using vertex_type = std::size_t;

    vertex_type add_vertex();
    void add_edge(vertex_type a, vertex_type b);

    bool has_vertex(vertex_type v) const;
    const std::vector<vertex_type>& neighbors(vertex_type v) const;

    std::size_t size() const;

    std::vector<vertex_type> vertices() const;

private:
    std::vector<std::vector<vertex_type>> adj_;
};