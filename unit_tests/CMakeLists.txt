cmake_minimum_required(VERSION 3.5)

add_library(athena_catch_main STATIC catch_tests_runner.cpp include/catch.hpp)
target_link_libraries(athena_catch_main PRIVATE athena_project_options)

add_executable(athenaUnitTests catch_tests_runner.cpp src/athena_function_tests.cpp src/grid_tests.cpp src/grid_view_tests.cpp)
target_link_libraries(athenaUnitTests PRIVATE athena_project_warnings athena_project_options athena_catch_main)
target_include_directories(athenaUnitTests PRIVATE ../include PUBLIC include)
target_compile_features(athenaUnitTests INTERFACE cxx_std_17)

include(CTest)