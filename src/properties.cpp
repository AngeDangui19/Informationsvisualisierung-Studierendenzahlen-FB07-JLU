#include "graph/properties.hpp"
#include "graph/algorithms.hpp"

#include <cstddef>
#include <queue>
#include <vector>

namespace graph {

bool is_dag(const DirectedGraph& graph) {
    const std::size_t n = graph.vertex_count();

    std::vector<std::size_t> indegree(n, 0);

    for (std::size_t vertex = 0; vertex < n; ++vertex) {
        for (const auto neighbor : graph.neighbors(vertex)) {
            ++indegree[neighbor];
        }
    }

    std::queue<std::size_t> queue;

    for (std::size_t vertex = 0; vertex < n; ++vertex) {
        if (indegree[vertex] == 0) {
            queue.push(vertex);
        }
    }

    std::size_t visited_count = 0;

    while (!queue.empty()) {
        const std::size_t current = queue.front();
        queue.pop();

        ++visited_count;

        for (const auto neighbor : graph.neighbors(current)) {
            --indegree[neighbor];

            if (indegree[neighbor] == 0) {
                queue.push(neighbor);
            }
        }
    }

    return visited_count == n;
}

bool is_tree(const UndirectedGraph& graph) {
    const std::size_t n = graph.vertex_count();

    if (n == 0) {
        return false;
    }

    const auto components = connected_components(graph);

    if (components.size() != 1) {
        return false;
    }

    return graph.edge_count() == n - 1;
}

bool has_only_positive_weights(const WeightedDirectedGraph& graph) {
    const std::size_t n = graph.vertex_count();

    for (std::size_t vertex = 0; vertex < n; ++vertex) {
        for (const auto& [neighbor, weight] : graph.weighted_neighbors(vertex)) {
            (void)neighbor;

            if (weight <= 0.0) {
                return false;
            }
        }
    }

    return true;
}

bool is_connected(const WeightedUndirectedGraph& graph) {
    const std::size_t n = graph.vertex_count();

    if (n == 0) {
        return false;
    }

    std::vector<bool> visited(n, false);
    std::queue<std::size_t> queue;

    visited[0] = true;
    queue.push(0);

    std::size_t visited_count = 0;

    while (!queue.empty()) {
        const std::size_t current = queue.front();
        queue.pop();

        ++visited_count;

        for (const auto& [neighbor, weight] : graph.weighted_neighbors(current)) {
            (void)weight;

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    return visited_count == n;
}

} // namespace graph