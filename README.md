# GraphLibrary

Small C++ graph library for:
- directed graphs
- undirected graphs
- weighted directed graphs
- weighted undirected graphs

## Implemented algorithms
- BFS
- DFS
- Topological Sort
- Dijkstra
- Bellman-Ford
- Prim
- Kruskal
- Connected Components

## Implemented properties
- is_dag
- is_tree
- has_only_positive_weights
- is_connected

## Build
```bash
mkdir build
cd build
cmake ..
cmake --build .

## Run Tests
ctest```
