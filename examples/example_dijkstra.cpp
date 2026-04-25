#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graph/algorithms.hpp"
#include "graph/weighted_directed_graph.hpp"

void export_to_graphviz(const WeightedDirectedGraph& g, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Error: could not open file " << filename << '\n';
        return;
    }

    file << "digraph G {\n";

    for (std::size_t v = 0; v < g.vertex_count(); ++v)
    {
        for (const auto& [neighbor, weight] : g.neighbors(v))
        {
            file << "    " << v << " -> " << neighbor
                 << " [label=\"" << weight << "\"];\n";
        }
    }

    file << "}\n";
}

int main() {

    WeightedDirectedGraph g;

    // add vertex
    auto v0 = g.add_vertex();
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    auto v3 = g.add_vertex();

    // add edges
    g.add_edge(v0, v1, 4.0);
    g.add_edge(v0, v2, 1.0);
    g.add_edge(v2, v1, 2.0);
    g.add_edge(v1, v3, 1.0);
    g.add_edge(v2, v3, 5.0);
 
    const auto distances = dijkstra(g, v0);

    std::cout << "Shortest distances from vertex " << v0 << ":\n";
    for (std::size_t i = 0; i < distances.size(); ++i) {
        std::cout << v0 << " -> " << i << " = " << distances[i] << '\n';
    }

    return 0;

}