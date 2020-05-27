cmake_minimum_required(VERSION 3.5)
project(AthenaTests)

find_package(Catch2 REQUIRED)

include_directories(../include)

add_executable(catchTests catch_tests_runner.cpp include/athena_function_tests.cpp)
target_link_libraries(catchTests Catch2::Catch2)
target_compile_features(Athena INTERFACE cxx_std_17)

include(CTest)
include(Catch)

catch_discover_tests(catchTests)