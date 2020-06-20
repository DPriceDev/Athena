cmake_minimum_required(VERSION 3.15)

# Build and Link Library

set(INCLUDES
        athena_functions.h
        athena_maths.h
        grid.h
        grid_view.h
        range.h
        rect.h
        vector.h)

add_library(athena INTERFACE)
target_include_directories(athena INTERFACE ${INCLUDES} ../include)
target_compile_features(athena INTERFACE cxx_std_17)