cmake_minimum_required(VERSION 3.21)
project(3lab3sem)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(google_test/google-test)
include_directories (google_test/google-test/googletest/include)
add_executable(3lab3sem main.cpp graph_tests.cpp)
target_link_libraries(3lab3sem gtest)