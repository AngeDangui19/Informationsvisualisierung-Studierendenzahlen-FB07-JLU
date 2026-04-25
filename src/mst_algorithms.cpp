#include "graph/algorithms.hpp"

#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
namespace {

class DisjointSet {
public:
    explicit DisjointSet(std::size_t size)
        : parent_(size), rank_(size, 0)
    {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    std::size_t find(std::size_t v) {
        if (parent_[v] != v) {
            parent_[v] = find(parent_[v]);
        }
        return parent_[v];
    }

    bool unite(std::size_t a, std::size_t b) {
        auto root_a = find(a);
        auto root_b = find(b);

        if (root_a == root_b) {
            return false;
        }

        if (rank_[root_a] < rank_[root_b]) {
            std::swap(root_a, root_b);
        }

        parent_[root_b] = root_a;

        if (rank_[root_a] == rank_[root_b]) {
            ++rank_[root_a];
        }

        return true;
    }

private:
    std::vector<std::size_t> parent_;
    std::vector<std::size_t> rank_;
};

} // namespace

std::vector<WeightedUndirectedGraph::Edge>
kruskal(const WeightedUndirectedGraph& graph)
{
    auto edges = graph.edges();

    std::sort(edges.begin(), edges.end(),
              [](const auto& a, const auto& b) {
                  return a.weight < b.weight;
              });

    DisjointSet ds(graph.vertex_count());
    std::vector<WeightedUndirectedGraph::Edge> mst;

    for (const auto& edge : edges) {
        if (ds.unite(edge.from, edge.to)) {
            mst.push_back(edge);
        }
    }

    return mst;
}

std::vector<WeightedUndirectedGraph::Edge>
prim(const WeightedUndirectedGraph& graph,
     WeightedUndirectedGraph::Vertex start)
{
    using Edge = WeightedUndirectedGraph::Edge;
    using Vertex = WeightedUndirectedGraph::Vertex;

    std::vector<Edge> mst;
    std::vector<bool> visited(graph.vertex_count(), false);

    auto compare = [](const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    };

    std::priority_queue<Edge, std::vector<Edge>, decltype(compare)> pq(compare);

    visited[start] = true;

    for (const auto& edge : graph.neighbors(start)) {
        pq.push(edge);
    }

    while (!pq.empty() && mst.size() < graph.vertex_count() - 1) {
        Edge edge = pq.top();
        pq.pop();

        Vertex next = edge.to;

        if (visited[next]) {
            continue;
        }

        mst.push_back(edge);
        visited[next] = true;

        for (const auto& next_edge : graph.neighbors(next)) {
            if (!visited[next_edge.to]) {
                pq.push(next_edge);
            }
        }
    }

    return mst;
}