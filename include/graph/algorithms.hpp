#pragma once

#include <cstddef>
#include <vector>

#include "graph/undirected_graph.hpp"

namespace graph {

std::vector<std::vector<std::size_t>>
connected_components(const UndirectedGraph& graph);

} // namespace graph