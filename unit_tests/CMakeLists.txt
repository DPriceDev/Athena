cmake_minimum_required(VERSION 3.5)

include_directories(../include)

add_executable(catchTests catch_tests_runner.cpp include/catch.hpp include/athena_function_tests.cpp)
target_compile_features(Athena INTERFACE cxx_std_17)

include(CTest)