#include "graph/undirected_graph.hpp"
#include "graph/algorithms/connectivity.hpp"
#include <iostream>

int main() {
    // --- Example 1: two distinct components ---
    std::cout << "=== Connected Components: two groups ===\n";

    UndirectedGraph g1;
    auto v0 = g1.add_vertex();
    auto v1 = g1.add_vertex();
    auto v2 = g1.add_vertex();
    auto v3 = g1.add_vertex();
    auto v4 = g1.add_vertex();
    auto v5 = g1.add_vertex();

    g1.add_edge(v0, v1);
    g1.add_edge(v1, v2);
    g1.add_edge(v3, v4);
    g1.add_edge(v4, v5);

    std::cout << "Graph: 0-1-2  and  3-4-5 (two components)\n";
    std::cout << "Number of components: " << graph::count_components(g1) << "\n";

    auto comps = graph::connected_components(g1);
    for (std::size_t i = 0; i < comps.size(); ++i) {
        std::cout << "  Component " << i << ": ";
        for (auto v : comps[i])
            std::cout << "v" << v << " ";
        std::cout << "\n";
    }
    std::cout << "\n";

    // --- Example 2: fully connected graph ---
    std::cout << "=== Connected Components: connected graph ===\n";

    UndirectedGraph g2;
    auto u0 = g2.add_vertex();
    auto u1 = g2.add_vertex();
    auto u2 = g2.add_vertex();
    auto u3 = g2.add_vertex();

    g2.add_edge(u0, u1);
    g2.add_edge(u1, u2);
    g2.add_edge(u2, u3);
    g2.add_edge(u3, u0);

    std::cout << "Graph: 0-1-2-3-0 (connected cycle)\n";
    std::cout << "Is connected: " << (graph::is_connected(g2) ? "yes" : "no") << "\n";
    std::cout << "Number of components: " << graph::count_components(g2) << "\n\n";

    // --- Example 3: isolated vertices ---
    std::cout << "=== Connected Components: isolated vertex ===\n";

    UndirectedGraph g3;
    g3.add_vertex(); // 0
    g3.add_vertex(); // 1
    g3.add_vertex(); // 2 — isolated
    g3.add_edge(0, 1);

    auto ids = graph::component_ids(g3);
    std::cout << "Graph: 0-1  2 (isolated vertex)\n";
    std::cout << "Component ID per vertex:\n";
    for (std::size_t i = 0; i < ids.size(); ++i)
        std::cout << "  v" << i << " -> component " << ids[i] << "\n";
    std::cout << "Number of components: " << graph::count_components(g3) << "\n";

    return 0;
}