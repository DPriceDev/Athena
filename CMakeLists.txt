cmake_minimum_required(VERSION 3.15)

project(Athena LANGUAGES CXX VERSION 1.0.0)
include(cmake/StandardProjectSettings.cmake)

add_library(athena_project_options INTERFACE)
target_compile_features(athena_project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(athena_project_options INTERFACE -ftime-trace)
    endif()
endif()

add_library(athena_project_warnings INTERFACE)

# enable cache system
#include(cmake/Cache.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(athena_project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(athena_project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    target_precompile_headers(
            athena_project_options
            INTERFACE
            <vector>
            <utility>
            <algorithm>
            <array>)
endif()

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")


set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES})
include(cmake/Conan.cmake)
run_conan()

# Add Source CmakeList
add_subdirectory(include)
add_library(athena::athena ALIAS athena)

# Enable catch2 Testing
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(ATHENA_ENABLE_TESTING TRUE)
endif()

if(ATHENA_ENABLE_TESTING)
    if(ENABLE_TESTING)
        enable_testing()
        message(
                "Building Unit Tests."
        )
        add_subdirectory(unit_tests PRIVATE)
    endif()
#todo: Add fuzz testing~
endif()