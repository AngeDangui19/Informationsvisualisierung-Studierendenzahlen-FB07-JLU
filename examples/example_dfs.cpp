#include "graph/directed_graph.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/algorithms/traversal.hpp"
#include <iostream>

int main() {
    // --- Example 1: BFS vs DFS comparison on the same graph ---
    std::cout << "=== BFS vs DFS comparison ===\n";

    DirectedGraph g1;
    auto v0 = g1.add_vertex();
    auto v1 = g1.add_vertex();
    auto v2 = g1.add_vertex();
    auto v3 = g1.add_vertex();
    auto v4 = g1.add_vertex();
    auto v5 = g1.add_vertex();

    g1.add_edge(v0, v1);
    g1.add_edge(v0, v2);
    g1.add_edge(v1, v3);
    g1.add_edge(v1, v4);
    g1.add_edge(v2, v5);

    std::cout << "Graph: 0->1, 0->2, 1->3, 1->4, 2->5\n";

    std::cout << "BFS from v0: ";
    for (auto v : graph::bfs(g1, v0))
        std::cout << "v" << v << " ";
    std::cout << "\n(visits neighbors first, level by level)\n";

    std::cout << "DFS from v0: ";
    for (auto v : graph::dfs(g1, v0))
        std::cout << "v" << v << " ";
    std::cout << "\n(follows one path as deep as possible before backtracking)\n\n";

    // --- Example 2: undirected graph with cycle ---
    std::cout << "=== DFS on undirected graph with cycle ===\n";

    UndirectedGraph g2;
    auto u0 = g2.add_vertex();
    auto u1 = g2.add_vertex();
    auto u2 = g2.add_vertex();
    auto u3 = g2.add_vertex();

    g2.add_edge(u0, u1);
    g2.add_edge(u1, u2);
    g2.add_edge(u2, u3);
    g2.add_edge(u3, u0);

    std::cout << "Graph: 0-1-2-3-0 (cycle)\n";
    std::cout << "DFS from v0: ";
    for (auto v : graph::dfs(g2, u0))
        std::cout << "v" << v << " ";
    std::cout << "\n(each vertex visited exactly once)\n\n";

    // --- Example 3: disconnected graph ---
    std::cout << "=== DFS on disconnected graph ===\n";

    DirectedGraph g3;
    auto a0 = g3.add_vertex();
    auto a1 = g3.add_vertex();
    auto a2 = g3.add_vertex(); // isolated
    g3.add_edge(a0, a1);

    std::cout << "Graph: 0->1  2 (isolated vertex)\n";
    std::cout << "DFS from v0: ";
    for (auto v : graph::dfs(g3, a0))
        std::cout << "v" << v << " ";
    std::cout << "\n(v2 not reached — disconnected graph)\n";

    return 0;
}