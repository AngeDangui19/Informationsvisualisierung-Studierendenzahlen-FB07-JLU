#pragma once

#include <vector>

namespace graph {

template <typename Graph>
std::vector<std::vector<typename Graph::vertex_type>>
connected_components(const Graph& g) {
    using V = typename Graph::vertex_type;

    std::vector<bool> visited(g.size(), false);
    std::vector<std::vector<V>> components;

    for (V start = 0; start < g.size(); ++start) {
        if (visited[start]) continue;

        std::vector<V> comp;
        std::vector<V> stack{start};

        visited[start] = true;

        while (!stack.empty()) {
            V v = stack.back();
            stack.pop_back();

            comp.push_back(v);

            for (auto u : g.neighbors(v)) {
                if (!visited[u]) {
                    visited[u] = true;
                    stack.push_back(u);
                }
            }
        }

        components.push_back(comp);
    }

    return components;
}

}