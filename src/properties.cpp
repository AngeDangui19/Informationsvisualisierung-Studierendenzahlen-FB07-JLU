#include "graph/properties.hpp"

#include <vector>
#include <stack>

namespace graph {

// -------- Directed Graph --------

static bool dfs_cycle(const DirectedGraph& g,
                      std::size_t v,
                      std::vector<bool>& visited,
                      std::vector<bool>& rec_stack) {
    visited[v] = true;
    rec_stack[v] = true;

    for (auto u : g.neighbors(v)) {
        if (!visited[u] && dfs_cycle(g, u, visited, rec_stack))
            return true;
        else if (rec_stack[u])
            return true;
    }

    rec_stack[v] = false;
    return false;
}

bool is_dag(const DirectedGraph& g) {
    std::vector<bool> visited(g.size(), false);
    std::vector<bool> rec_stack(g.size(), false);

    for (std::size_t v = 0; v < g.size(); ++v) {
        if (!visited[v] && dfs_cycle(g, v, visited, rec_stack))
            return false;
    }

    return true;
}

// -------- Undirected Graph --------

bool is_tree(const UndirectedGraph& g) {
    if (g.size() == 0) return true;

    std::vector<bool> visited(g.size(), false);
    std::stack<std::pair<std::size_t, std::size_t>> s;

    s.push({0, static_cast<std::size_t>(-1)});
    visited[0] = true;

    while (!s.empty()) {
        auto [v, parent] = s.top();
        s.pop();

        for (auto u : g.neighbors(v)) {
            if (!visited[u]) {
                visited[u] = true;
                s.push({u, v});
            } else if (u != parent) {
                return false;
            }
        }
    }

    for (bool v : visited)
        if (!v) return false;

    return true;
}

// -------- Weighted Directed Graph --------

bool has_only_positive_weights(const WeightedDirectedGraph& g) {
    for (std::size_t v = 0; v < g.size(); ++v) {
        for (const auto& edge : g.neighbors(v)) {
            if (edge.weight < 0)
                return false;
        }
    }
    return true;
}

// -------- Weighted Undirected Graph --------

bool is_connected(const WeightedUndirectedGraph& g) {
    if (g.size() == 0) return true;

    std::vector<bool> visited(g.size(), false);
    std::stack<std::size_t> s;

    s.push(0);
    visited[0] = true;

    while (!s.empty()) {
        auto v = s.top();
        s.pop();

        for (const auto& edge : g.neighbors(v)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                s.push(edge.to);
            }
        }
    }

    for (bool v : visited)
        if (!v) return false;

    return true;
}

} // namespace graph