#pragma once

#include <vector>
#include <queue>
#include <stack>

namespace graph {

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

        for (auto u : g.neighbors(v)) {
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

        for (auto u : g.neighbors(v)) {
            if (!visited[u]) {
                s.push(u);
            }
        }
    }

    return order;
}

// Topological Sort
template <typename Graph>
std::vector<typename Graph::vertex_type>
topological_sort(const Graph& g) {
    using V = typename Graph::vertex_type;

    std::vector<int> indegree(g.size(), 0);

    for (auto v : g.vertices()) {
        for (auto u : g.neighbors(v)) {
            indegree[u]++;
        }
    }

    std::queue<V> q;
    for (V v = 0; v < g.size(); ++v) {
        if (indegree[v] == 0)
            q.push(v);
    }

    std::vector<V> order;

    while (!q.empty()) {
        V v = q.front(); q.pop();
        order.push_back(v);

        for (auto u : g.neighbors(v)) {
            if (--indegree[u] == 0)
                q.push(u);
        }
    }

    return order;
}

}