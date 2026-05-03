# =========================
# Fetch Catch2
# =========================
include(FetchContent)

FetchContent_Declare(
  Catch2
  URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(Catch2)

# =========================
# Catch2 CMake helpers
# =========================
include(Catch)

# =========================
# Helper macro
# =========================
function(add_graph_test name)
    add_executable(${name} ${name}.cpp)

    target_link_libraries(${name}
        PRIVATE
        graphlib
        Catch2::Catch2WithMain
    )

    catch_discover_tests(${name})
endfunction()

# =========================
# All tests
# =========================
add_graph_test(test_graphs)
add_graph_test(test_bfs)
add_graph_test(test_dfs)
add_graph_test(test_topological_sort)
add_graph_test(test_dijkstra)
add_graph_test(test_bellman_ford)
add_graph_test(test_prim)
add_graph_test(test_kruskal)
add_graph_test(test_connected_components)
add_graph_test(test_properties)