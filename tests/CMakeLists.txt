include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_graphs test_graphs.cpp)
target_link_libraries(test_graphs PRIVATE graphlib GTest::gtest_main)

add_executable(test_bfs test_bfs.cpp)
target_link_libraries(test_bfs PRIVATE graphlib GTest::gtest_main)

add_executable(test_dfs test_dfs.cpp)
target_link_libraries(test_dfs PRIVATE graphlib GTest::gtest_main)

add_executable(test_topological_sort test_topological_sort.cpp)
target_link_libraries(test_topological_sort PRIVATE graphlib GTest::gtest_main)

add_executable(test_dijkstra test_dijkstra.cpp)
target_link_libraries(test_dijkstra PRIVATE graphlib GTest::gtest_main)

add_executable(test_prim test_prim.cpp)
target_link_libraries(test_prim PRIVATE graphlib GTest::gtest_main)

add_executable(test_kruskal test_kruskal.cpp)
target_link_libraries(test_kruskal PRIVATE graphlib GTest::gtest_main)

add_executable(test_connected_components test_connected_components.cpp)
target_link_libraries(test_connected_components PRIVATE graphlib GTest::gtest_main)

add_executable(test_properties test_properties.cpp)
target_link_libraries(test_properties PRIVATE graphlib GTest::gtest_main)

add_executable(test_bellman_ford test_bellman_ford.cpp)
target_link_libraries(test_bellman_ford PRIVATE graphlib GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(test_graphs)
gtest_discover_tests(test_bfs)
gtest_discover_tests(test_dfs)
gtest_discover_tests(test_topological_sort)
gtest_discover_tests(test_dijkstra)
gtest_discover_tests(test_prim)
gtest_discover_tests(test_kruskal)
gtest_discover_tests(test_connected_components)
gtest_discover_tests(test_properties)
gtest_discover_tests(test_bellman_ford)