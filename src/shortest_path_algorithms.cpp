#include "graph/algorithms.hpp"

#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include <stdexcept>

std::vector<double> dijkstra(const WeightedDirectedGraph& graph,
                             WeightedDirectedGraph::Vertex source)
{
    using Vertex = WeightedDirectedGraph::Vertex;
    using DistanceVertexPair = std::pair<double, Vertex>;

    const double infinity = std::numeric_limits<double>::infinity();

    std::vector<double> distances(graph.vertex_count(), infinity);
    distances[source] = 0.0;

    std::priority_queue<
        DistanceVertexPair,
        std::vector<DistanceVertexPair>,
        std::greater<DistanceVertexPair>
    > pq;

    pq.push({0.0, source});

    while (!pq.empty()) {
        const auto [current_distance, current_vertex] = pq.top();
        pq.pop();

        if (current_distance > distances[current_vertex]) {
            continue;
        }

        for (const auto& [neighbor, weight] : graph.neighbors(current_vertex)) {
            const double new_distance = current_distance + weight;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push({new_distance, neighbor});
            }
        }
    }

    return distances;
}

std::vector<double> bellman_ford(const WeightedDirectedGraph& graph,
                                 WeightedDirectedGraph::Vertex source)
{
    using Vertex = WeightedDirectedGraph::Vertex;

    const double infinity = std::numeric_limits<double>::infinity();
    std::vector<double> distances(graph.vertex_count(), infinity);
    distances[source] = 0.0;

    for (std::size_t i = 0; i < graph.vertex_count() - 1; ++i) {
        bool updated = false;

        for (Vertex u = 0; u < graph.vertex_count(); ++u) {
            if (distances[u] == infinity) {
                continue;
            }

            for (const auto& [v, weight] : graph.neighbors(u)) {
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    updated = true;
                }
            }
        }

        if (!updated) {
            break;
        }
    }

    for (Vertex u = 0; u < graph.vertex_count(); ++u) {
        if (distances[u] == infinity) {
            continue;
        }

        for (const auto& [v, weight] : graph.neighbors(u)) {
            if (distances[u] + weight < distances[v]) {
                throw std::runtime_error("Negative-weight cycle detected");
            }
        }
    }

    return distances;
}