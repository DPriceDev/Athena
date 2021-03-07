cmake_minimum_required(VERSION 3.5)

if(CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

set(SRC
        athena_function_tests.cpp
        grid_tests.cpp
        grid_view_tests.cpp
        grid_row_iterator_tests.cpp
        grid_column_iterator_tests.cpp
        athena_maths_tests.cpp
        range_tests.cpp
        rect_tests.cpp
        grid_view_row_iterator_tests.cpp
        grid_view_column_iterator_tests.cpp)

add_executable(athena_unit_tests ${SRC})
target_link_libraries(athena_unit_tests
        PRIVATE
        athena_project_warnings
        athena_project_options
        athena_catch_main)
target_include_directories(athena_unit_tests
        PRIVATE
        ../include
        ../../include)

# automatically discover tests that are defined in catch based test files
catch_discover_tests(
        athena_unit_tests
        TEST_PREFIX
        "unittests."
        REPORTER
        xml
        OUTPUT_DIR
        .
        OUTPUT_PREFIX
        "unittests."
        OUTPUT_SUFFIX
        .xml)