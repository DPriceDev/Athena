cmake_minimum_required(VERSION 3.5)

add_library(athena_catch_main STATIC catch_tests_runner.cpp)
target_link_libraries(athena_catch_main
        PRIVATE
        athena_project_options
        athena_project_warnings
        CONAN_PKG::catch2)

add_subdirectory(src)