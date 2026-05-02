#pragma once

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace graph {

template <typename Graph>
std::vector<std::tuple<
    typename Graph::vertex_type,
    typename Graph::vertex_type,
    typename Graph::weight_type
>>
prim(const Graph& graph, typename Graph::vertex_type start) {
    using Vertex = typename Graph::vertex_type;
    using Weight = typename Graph::weight_type;
    using EdgeResult = std::tuple<Vertex, Vertex, Weight>;
    using QueueElement = std::tuple<Weight, Vertex, Vertex>;

    if (!graph.has_vertex(start)) {
        throw std::out_of_range("Invalid start vertex.");
    }

    std::vector<bool> visited(graph.size(), false);
    std::vector<EdgeResult> mst;

    std::priority_queue<
        QueueElement,
        std::vector<QueueElement>,
        std::greater<>
    > queue;

    visited[start] = true;

    for (const auto& edge : graph.neighbors(start)) {
        queue.emplace(edge.weight, start, edge.to);
    }

    while (!queue.empty()) {
        auto [weight, from, to] = queue.top();
        queue.pop();

        if (visited[to]) {
            continue;
        }

        visited[to] = true;
        mst.emplace_back(from, to, weight);

        for (const auto& edge : graph.neighbors(to)) {
            if (!visited[edge.to]) {
                queue.emplace(edge.weight, to, edge.to);
            }
        }
    }

    return mst;
}

template <typename Vertex>
class DisjointSet {
public:
    explicit DisjointSet(std::size_t size)
        : parent_(size), rank_(size, 0) {
        for (Vertex v = 0; v < size; ++v) {
            parent_[v] = v;
        }
    }

    Vertex find(Vertex v) {
        if (parent_[v] != v) {
            parent_[v] = find(parent_[v]);
        }

        return parent_[v];
    }

    bool unite(Vertex a, Vertex b) {
        Vertex root_a = find(a);
        Vertex root_b = find(b);

        if (root_a == root_b) {
            return false;
        }

        if (rank_[root_a] < rank_[root_b]) {
            parent_[root_a] = root_b;
        } else if (rank_[root_a] > rank_[root_b]) {
            parent_[root_b] = root_a;
        } else {
            parent_[root_b] = root_a;
            ++rank_[root_a];
        }

        return true;
    }

private:
    std::vector<Vertex> parent_;
    std::vector<std::size_t> rank_;
};

template <typename Graph>
std::vector<std::tuple<
    typename Graph::vertex_type,
    typename Graph::vertex_type,
    typename Graph::weight_type
>>
kruskal(const Graph& graph) {
    using Vertex = typename Graph::vertex_type;
    using Weight = typename Graph::weight_type;
    using EdgeResult = std::tuple<Vertex, Vertex, Weight>;

    std::vector<EdgeResult> edges;

    for (Vertex from : graph) {
        for (const auto& edge : graph.neighbors(from)) {
            edges.emplace_back(from, edge.to, edge.weight);
        }
    }

    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    DisjointSet<Vertex> sets(graph.size());
    std::vector<EdgeResult> mst;

    for (const auto& [from, to, weight] : edges) {
        if (sets.unite(from, to)) {
            mst.emplace_back(from, to, weight);
        }
    }

    return mst;
}

}