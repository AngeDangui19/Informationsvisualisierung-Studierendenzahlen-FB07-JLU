cmake_minimum_required(VERSION 3.16)

project(GraphLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(graphlib
    src/directed_graph.cpp
    src/undirected_graph.cpp
    src/weighted_directed_graph.cpp
    src/weighted_undirected_graph.cpp
    src/traversal_algorithms.cpp
    src/shortest_path_algorithms.cpp
    src/mst_algorithms.cpp
    src/connectivity_algorithms.cpp
    src/properties.cpp
)

target_include_directories(graphlib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)
add_subdirectory(examples)