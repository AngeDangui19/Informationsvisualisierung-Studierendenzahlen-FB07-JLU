#pragma once

#include <vector>
#include <stdexcept>

namespace graph {

namespace detail {

template <typename T>
auto get_target(const T& neighbor) -> decltype(neighbor.to) {
    return neighbor.to;
}

inline std::size_t get_target(std::size_t v) {
    return v;
}

} // namespace detail

// Retourne la liste des composantes connexes
// Chaque composante est un vecteur de sommets
template <typename Graph>
std::vector<std::vector<typename Graph::vertex_type>>
connected_components(const Graph& g) {
    using V = typename Graph::vertex_type;

    std::vector<bool> visited(g.size(), false);
    std::vector<std::vector<V>> components;

    for (V start = 0; start < static_cast<V>(g.size()); ++start) {
        if (visited[start]) continue;

        std::vector<V> comp;
        std::vector<V> stack{start};
        visited[start] = true;

        while (!stack.empty()) {
            V v = stack.back();
            stack.pop_back();
            comp.push_back(v);

            for (const auto& neighbor : g.neighbors(v)) {
                V u = detail::get_target(neighbor);
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

// Retourne le nombre de composantes connexes
template <typename Graph>
std::size_t count_components(const Graph& g) {
    return connected_components(g).size();
}

// Retourne pour chaque sommet l'ID de sa composante (0, 1, 2, ...)
// component_ids[v] = ID de la composante du sommet v
template <typename Graph>
std::vector<int>
component_ids(const Graph& g) {
    using V = typename Graph::vertex_type;

    std::vector<int> ids(g.size(), -1);
    int current_id = 0;

    for (V start = 0; start < static_cast<V>(g.size()); ++start) {
        if (ids[start] != -1) continue;

        std::vector<V> stack{start};
        ids[start] = current_id;

        while (!stack.empty()) {
            V v = stack.back();
            stack.pop_back();

            for (const auto& neighbor : g.neighbors(v)) {
                V u = detail::get_target(neighbor);
                if (ids[u] == -1) {
                    ids[u] = current_id;
                    stack.push_back(u);
                }
            }
        }

        ++current_id;
    }

    return ids;
}

// Retourne true si le graphe est connexe (une seule composante)
template <typename Graph>
bool is_connected(const Graph& g) {
    if (g.empty()) return true;
    return count_components(g) == 1;
}

} // namespace graph