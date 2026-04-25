#include "graph/algorithms.hpp"

#include <cstddef>
#include <queue>
#include <vector>

namespace graph {

std::vector<std::vector<std::size_t>>
connected_components(const UndirectedGraph& graph) {
    const std::size_t n = graph.vertex_count();

    std::vector<bool> visited(n, false);
    std::vector<std::vector<std::size_t>> components;

    for (std::size_t start = 0; start < n; ++start) {
        if (visited[start]) {
            continue;
        }

        std::vector<std::size_t> component;
        std::queue<std::size_t> queue;

        visited[start] = true;
        queue.push(start);

        while (!queue.empty()) {
            const std::size_t current = queue.front();
            queue.pop();

            component.push_back(current);

            for (const auto neighbor : graph.neighbors(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }

        components.push_back(component);
    }

    return components;
}

} // namespace graph