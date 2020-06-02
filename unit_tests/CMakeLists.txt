cmake_minimum_required(VERSION 3.5)

include_directories(../include)

add_library(catch_main STATIC catch_tests_runner.cpp include/catch.hpp)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(catchTests catch_tests_runner.cpp src/athena_function_tests.cpp src/grid_tests.cpp src/grid_view_tests.cpp)
target_link_libraries(catchTests PRIVATE project_warnings project_options catch_main)
target_compile_features(Athena INTERFACE cxx_std_17)

include(CTest)