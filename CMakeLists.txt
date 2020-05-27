cmake_minimum_required(VERSION 3.5)

project(Athena LANGUAGES CXX VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 17)

add_library(Athena INTERFACE)
target_include_directories(Athena INTERFACE include/*)
target_compile_features(Athena INTERFACE cxx_std_17)

enable_testing()
add_subdirectory(unit_tests)