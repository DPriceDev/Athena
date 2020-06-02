cmake_minimum_required(VERSION 3.5)

project(Athena LANGUAGES CXX VERSION 1.0.0)
include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

add_library(project_warnings INTERFACE)

# enable cache system
#include(cmake/Cache.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    target_precompile_headers(project_options INTERFACE <vector> <utility> <algorithm> <array>)
endif()

# Build and Link Library
add_library(Athena INTERFACE)
target_link_libraries(Athena INTERFACE project_warnings project_options)
target_include_directories(Athena INTERFACE include/*)
target_compile_features(Athena INTERFACE cxx_std_17)

# Enable catch2 Testing
if(ENABLE_TESTING)
    enable_testing()
    message(
            "Building Unit Tests."
    )
    add_subdirectory(unit_tests PRIVATE)
endif()

#todo: Add fuzz testing~