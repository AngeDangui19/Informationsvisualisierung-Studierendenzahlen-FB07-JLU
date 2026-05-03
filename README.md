# Graph Library (C++)

This project implements a small reusable C++ graph library. It supports directed,
undirected, weighted directed, and weighted undirected graphs, together with
commonly used graph algorithms, examples, and unit tests.

---

## Graph Types

The following graph structures are implemented:

- Directed Graph
- Undirected Graph
- Weighted Directed Graph
- Weighted Undirected Graph

---

## Implemented Algorithms and Supported Graph Types

The following algorithms have been implemented, along with the types of graphs
they support:

| Algorithm            | Supported Graph Type        |
| -------------------- | --------------------------- |
| BFS                  | Directed / Undirected Graph |
| DFS                  | Directed / Undirected Graph |
| Topological Sort     | Directed Graph              |
| Connected Components | Undirected Graph            |
| Dijkstra             | Weighted Directed Graph     |
| Bellman-Ford         | Weighted Directed Graph     |
| Kruskal              | Weighted Undirected Graph   |
| Prim                 | Weighted Undirected Graph   |

Each algorithm is implemented in a modular way and can be reused independently
depending on the type of graph and the problem being solved.

---

## Project Structure

```text
GraphLibrary/
├── include/graph/              # Public headers
├── include/graph/algorithms/   # Template-based graph algorithms
├── src/                        # Container implementations
├── examples/                   # Example programs
├── tests/                      # Catch2 unit tests
└── CMakeLists.txt
```

---

## Compilation

The project uses **CMake**.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Running Examples

Example programs are provided to demonstrate the usage of each algorithm:

- example_bfs.cpp
- example_dfs.cpp
- example_toposort.cpp
- example_dijkstra.cpp
- example_prim.cpp
- example_kruskal.cpp
- example_connected_components.cpp
- example_properties.cpp

Run an example from the build directory:

```bash
./examples/example_dijkstra
```

---

## Tests

The project uses Catch2 for unit testing. To run the tests:

```bash
cd build
ctest
```

---

---

## Usage

1. Include the necessary headers:

```c++
#include "graph/weighted_directed_graph.hpp"
#include "graph/algorithms/shortest_path.hpp"
```

2. Create a graph:

```c++
auto v0 = graph.add_vertex("v0");
auto v1 = graph.add_vertex("v1");
auto v2 = graph.add_vertex("v2");

graph.add_edge(v0, v1, 4.0);
graph.add_edge(v0, v2, 1.0);
graph.add_edge(v2, v1, 2.0);
```

3. Run an algorithm:

```c++
auto distances = dijkstra(g, v0);
```

---

## Using the Library in Another CMake Project

```bash
add_subdirectory(GraphLibrary)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE graphlib)
```

Then include headers normally:

```c++
#include "graph/weighted_directed_graph.hpp"
#include "graph/algorithms/shortest_path.hpp"
```

---

## Contributions

| Member                      | Contributions                                                                                                                                                                                                       |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Klossouan Dangui Melchi** | Implemented graph structures (`DirectedGraph`, `UndirectedGraph`), traversal algorithms (BFS, DFS, Topological Sort), and corresponding examples and tests                                                          |
| **Leyla Louache**           | Implemented weighted graph structures (`WeightedDirectedGraph`, `WeightedUndirectedGraph`), shortest path algorithms (Dijkstra, Bellman-Ford), MST algorithms (Prim, Kruskal), and corresponding examples and tests |
| **Eltantawy Mohamed**       | Implemented connected components, graph properties (`is_dag`, `is_tree`, `is_connected`, etc.), global tests, project configuration (CMake), and documentation (README)                                             |

---
