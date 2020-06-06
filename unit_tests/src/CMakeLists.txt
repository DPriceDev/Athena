cmake_minimum_required(VERSION 3.5)

set(SRC
        athena_function_tests.cpp
        grid_tests.cpp
        grid_view_tests.cpp
        grid_row_iterator_tests.cpp
        grid_column_iterator_tests.cpp)

add_executable(athenaUnitTests ../catch_tests_runner.cpp ${SRC})
target_link_libraries(athenaUnitTests PRIVATE athena_project_warnings athena_project_options athena_catch_main)
target_include_directories(athenaUnitTests PRIVATE ../../include PUBLIC ../include)
target_compile_features(athenaUnitTests INTERFACE cxx_std_17)

include(CTest)