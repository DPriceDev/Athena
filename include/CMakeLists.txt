cmake_minimum_required(VERSION 3.15)

# Build and Link Library
add_library(athena INTERFACE)
target_include_directories(athena INTERFACE ../include)
target_compile_features(athena INTERFACE cxx_std_17)