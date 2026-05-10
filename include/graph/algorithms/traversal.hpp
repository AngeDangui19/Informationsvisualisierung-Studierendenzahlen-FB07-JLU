#pragma once

#include <queue>
#include <stack>
#include <vector>

namespace graph {

// Helper pour extraire le sommet cible depuis un voisin,
// qu'il soit un simple entier (graphes non pondérés)
// ou une struct Edge avec un champ .to (graphes pondérés)
namespace detail {

template <typename T>
auto get_target(const T& neighbor) -> decltype(neighbor.to) {
    return neighbor.to;
}

inline std::size_t get_target(std::size_t v) {
    return v;
}

} // namespace detail

// BFS
template <typename Graph>
std::vector<typename Graph::vertex_type>
bfs(const Graph& g, typename Graph::vertex_type start) {
    using V = typename Graph::vertex_type;

    std::vector<bool> visited(g.size(), false);
    std::vector<V> order;
    std::queue<V> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        V v = q.front(); q.pop();
        order.push_back(v);

        for (const auto& neighbor : g.neighbors(v)) {
            V u = detail::get_target(neighbor);
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }

    return order;
}

// DFS
template <typename Graph>
std::vector<typename Graph::vertex_type>
dfs(const Graph& g, typename Graph::vertex_type start) {
    using V = typename Graph::vertex_type;

    std::vector<bool> visited(g.size(), false);
    std::vector<V> order;
    std::stack<V> s;

    s.push(start);

    while (!s.empty()) {
        V v = s.top(); s.pop();

        if (visited[v]) continue;
        visited[v] = true;
        order.push_back(v);

        for (const auto& neighbor : g.neighbors(v)) {
            V u = detail::get_target(neighbor);
            if (!visited[u])
                s.push(u);
        }
    }

    return order;
}

// Topological Sort (graphes orientés uniquement)
template <typename Graph>
std::vector<typename Graph::vertex_type>
topological_sort(const Graph& g) {
    using V = typename Graph::vertex_type;

    std::vector<int> indegree(g.size(), 0);

    for (auto v : g.vertices())
        for (const auto& neighbor : g.neighbors(v))
            indegree[detail::get_target(neighbor)]++;

    std::queue<V> q;
    for (V v = 0; v < static_cast<V>(g.size()); ++v)
        if (indegree[v] == 0)
            q.push(v);

    std::vector<V> order;

    while (!q.empty()) {
        V v = q.front(); q.pop();
        order.push_back(v);

        for (const auto& neighbor : g.neighbors(v)) {
            V u = detail::get_target(neighbor);
            if (--indegree[u] == 0)
                q.push(u);
        }
    }

    return order;
}

} // namespace graph