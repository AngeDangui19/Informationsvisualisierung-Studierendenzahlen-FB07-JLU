#include "graph/directed_graph.hpp"
#include "graph/algorithms/traversal.hpp"
#include <iostream>

int main() {
    // --- Example 1: course dependency ordering ---
    std::cout << "=== Topological Sort: course dependencies ===\n";

    DirectedGraph g1;
    auto math   = g1.add_vertex(); // 0
    auto algo   = g1.add_vertex(); // 1
    auto prog   = g1.add_vertex(); // 2
    auto project = g1.add_vertex(); // 3
    auto exam   = g1.add_vertex(); // 4

    // math and prog are prerequisites for algo
    g1.add_edge(math, algo);
    g1.add_edge(prog, algo);
    // algo is a prerequisite for project and exam
    g1.add_edge(algo, project);
    g1.add_edge(algo, exam);

    std::cout << "Courses: math(0), algo(1), prog(2), project(3), exam(4)\n";
    std::cout << "Dependencies: math->algo, prog->algo, algo->project, algo->exam\n";
    std::cout << "Valid order: ";
    for (auto v : graph::topological_sort(g1))
        std::cout << v << " ";
    std::cout << "\n(math and prog must come before algo, algo before project and exam)\n\n";

    // --- Example 2: simple linear chain ---
    std::cout << "=== Topological Sort: linear chain ===\n";

    DirectedGraph g2;
    auto s0 = g2.add_vertex();
    auto s1 = g2.add_vertex();
    auto s2 = g2.add_vertex();
    auto s3 = g2.add_vertex();

    g2.add_edge(s0, s1);
    g2.add_edge(s1, s2);
    g2.add_edge(s2, s3);

    std::cout << "Graph: 0->1->2->3\n";
    std::cout << "Order: ";
    for (auto v : graph::topological_sort(g2))
        std::cout << v << " ";
    std::cout << "\n(only one valid order: 0 1 2 3)\n\n";

    // --- Example 3: graph with cycle (incomplete result) ---
    std::cout << "=== Topological Sort: graph with cycle ===\n";

    DirectedGraph g3;
    auto c0 = g3.add_vertex();
    auto c1 = g3.add_vertex();
    auto c2 = g3.add_vertex();

    g3.add_edge(c0, c1);
    g3.add_edge(c1, c2);
    g3.add_edge(c2, c0); // cycle

    auto order = graph::topological_sort(g3);
    std::cout << "Graph: 0->1->2->0 (cycle)\n";
    std::cout << "Result: ";
    for (auto v : order)
        std::cout << v << " ";
    std::cout << "\n";
    if (order.size() < g3.size())
        std::cout << "Incomplete sort: cycle detected ("
                  << order.size() << "/" << g3.size()
                  << " vertices ordered)\n";

    return 0;
}