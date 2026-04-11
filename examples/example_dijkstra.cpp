#include <iostream>
#include "graph/weighted_directed_graph.hpp"

int main() {

    WeightedDirectedGraph g;

    // ajouter des sommets
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    // ajouter des arêtes pondérées
    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);

    std::cout << "Vertex count: " << g.vertex_count() << std::endl;
    std::cout << "Edge count: " << g.edge_count() << std::endl;

    std::cout << "\nGraph adjacency list:\n";

    for (std::size_t v = 0; v < g.vertex_count(); ++v) {
        std::cout << v << " -> ";

        for (const auto& [neighbor, weight] : g.neighbors(v)) {
            std::cout << "(" << neighbor << ", w=" << weight << ") ";
        }

        std::cout << std::endl;
    }

    return 0;
}