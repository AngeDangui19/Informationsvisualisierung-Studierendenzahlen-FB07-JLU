#pragma once

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <vector>

class UndirectedGraph {
public:
    using vertex_type = std::size_t;

    // Modification
    vertex_type add_vertex();
    void add_edge(vertex_type a, vertex_type b);

    // Query
    bool has_vertex(vertex_type v) const;
    bool has_edge(vertex_type a, vertex_type b) const;

    const std::vector<vertex_type>& neighbors(vertex_type v) const;
    std::vector<std::pair<vertex_type, vertex_type>> edges() const;

    std::size_t size() const;
    std::size_t edge_count() const;
    std::size_t degree(vertex_type v) const;
    bool empty() const;

    std::vector<vertex_type> vertices() const;

    // Output
    void to_graphviz(std::ostream& os) const;

private:
    std::vector<std::vector<vertex_type>> adj_;
};