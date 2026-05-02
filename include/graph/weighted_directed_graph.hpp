#pragma once

#include <cstddef>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

class WeightedDirectedGraph {
public:
    // ===== Types =====
    using Vertex = std::size_t;
    using Weight = double;

    using vertex_type = Vertex;
    using weight_type = Weight;
    using size_type = std::size_t;

    struct VertexProperty {
        std::string name;
    };

    struct Edge {
        Vertex to;
        Weight weight;
        std::string label;
    };

    using edge_type = Edge;

    // ===== Iterator =====
    class vertex_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Vertex;
        using difference_type = std::ptrdiff_t;
        using pointer = const Vertex*;
        using reference = Vertex;

        explicit vertex_iterator(Vertex current);

        reference operator*() const;
        vertex_iterator& operator++();
        vertex_iterator operator++(int);

        bool operator==(const vertex_iterator& other) const;
        bool operator!=(const vertex_iterator& other) const;

    private:
        Vertex current_;
    };

    // ===== Constructors =====
    WeightedDirectedGraph() = default;

    // ===== Modification =====
    Vertex add_vertex(const std::string& name = "");
    void add_edge(Vertex from, Vertex to, Weight weight, const std::string& label = "");

    void clear();

    // ===== Query =====
    [[nodiscard]] bool has_vertex(Vertex v) const;
    [[nodiscard]] bool has_edge(Vertex from, Vertex to) const;

    [[nodiscard]] const std::vector<Edge>& neighbors(Vertex v) const;
    [[nodiscard]] const VertexProperty& vertex_property(Vertex v) const;

    [[nodiscard]] size_type size() const;
    [[nodiscard]] size_type vertex_count() const;
    [[nodiscard]] size_type edge_count() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_type degree(Vertex v) const;

    [[nodiscard]] std::vector<Vertex> vertices() const;

    // ===== Iterators =====
    vertex_iterator begin() const;
    vertex_iterator end() const;

    vertex_iterator cbegin() const;
    vertex_iterator cend() const;

    // ===== Output =====
    void to_graphviz(std::ostream& os) const;

private:
    std::vector<std::vector<Edge>> adjacency_list_;
    std::vector<VertexProperty> vertex_properties_;
    size_type edge_count_{0};

    void check_vertex(Vertex v) const;
};