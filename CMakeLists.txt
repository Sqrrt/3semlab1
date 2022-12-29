cmake_minimum_required(VERSION 3.21)
project(lab23sem)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(google_test/google-test)

include_directories (google_test/google-test/googletest/include)
add_executable(lab23sem main.cpp tests_for_hash_table.cpp)
target_link_libraries(lab23sem gtest)
