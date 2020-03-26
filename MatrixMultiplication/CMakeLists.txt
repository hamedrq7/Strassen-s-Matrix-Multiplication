# cmake_minimum_required(VERSION <specify CMake version here>)
project(MatrixMultiplication)

set(CMAKE_CXX_STANDARD 14)

add_executable(MatrixMultiplication main.cpp matrix.cpp matrix.h)