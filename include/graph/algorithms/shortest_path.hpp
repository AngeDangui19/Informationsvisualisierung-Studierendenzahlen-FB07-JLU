#pragma once

#include <algorithm>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace graph {

template <typename Graph>
struct DijkstraResult {
    using Vertex = typename Graph::vertex_type;
    using Weight = typename Graph::weight_type;

    std::vector<Weight> distances;
    std::vector<std::optional<Vertex>> parents;
};

template <typename Graph>
DijkstraResult<Graph>
dijkstra(const Graph& graph, typename Graph::vertex_type start) {
    using Vertex = typename Graph::vertex_type;
    using Weight = typename Graph::weight_type;

    if (!graph.has_vertex(start)) {
        throw std::out_of_range("Invalid start vertex.");
    }

    const Weight INF = std::numeric_limits<Weight>::infinity();

    std::vector<Weight> dist(graph.size(), INF);
    std::vector<std::optional<Vertex>> parent(graph.size(), std::nullopt);

    dist[start] = 0;

    using QueueElement = std::pair<Weight, Vertex>;

    std::priority_queue<
        QueueElement,
        std::vector<QueueElement>,
        std::greater<>
    > queue;

    queue.emplace(0, start);

    while (!queue.empty()) {
        auto [current_dist, current] = queue.top();
        queue.pop();

        if (current_dist > dist[current]) {
            continue;
        }

        for (const auto& edge : graph.neighbors(current)) {
            Vertex next = edge.to;
            Weight new_dist = dist[current] + edge.weight;

            if (new_dist < dist[next]) {
                dist[next] = new_dist;
                parent[next] = current;
                queue.emplace(new_dist, next);
            }
        }
    }

    return DijkstraResult<Graph>{dist, parent};
}

template <typename Graph>
std::vector<typename Graph::vertex_type>
reconstruct_path(
    typename Graph::vertex_type target,
    const std::vector<std::optional<typename Graph::vertex_type>>& parent
) {
    using Vertex = typename Graph::vertex_type;

    std::vector<Vertex> path;

    for (std::optional<Vertex> current = target; current.has_value(); current = parent[*current]) {
        path.push_back(*current);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

// Bellman-Ford reste comme avant
template <typename Graph>
std::vector<typename Graph::weight_type>
bellman_ford(const Graph& graph, typename Graph::vertex_type start) {
    using Vertex = typename Graph::vertex_type;
    using Weight = typename Graph::weight_type;

    if (!graph.has_vertex(start)) {
        throw std::out_of_range("Invalid start vertex.");
    }

    const Weight INF = std::numeric_limits<Weight>::infinity();

    std::vector<Weight> dist(graph.size(), INF);
    dist[start] = 0;

    for (std::size_t i = 0; i + 1 < graph.size(); ++i) {
        for (Vertex from : graph) {
            if (dist[from] == INF) {
                continue;
            }

            for (const auto& edge : graph.neighbors(from)) {
                Vertex to = edge.to;

                if (dist[from] + edge.weight < dist[to]) {
                    dist[to] = dist[from] + edge.weight;
                }
            }
        }
    }

    for (Vertex from : graph) {
        if (dist[from] == INF) {
            continue;
        }

        for (const auto& edge : graph.neighbors(from)) {
            Vertex to = edge.to;

            if (dist[from] + edge.weight < dist[to]) {
                throw std::runtime_error("Negative cycle detected.");
            }
        }
    }

    return dist;
}

}