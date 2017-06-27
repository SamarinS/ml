cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(svm)

set(SOURCE_LIB base.cpp base_matrix.cpp dense_matrix.cpp sparse_matrix.cpp
    solve_qp.cpp svm.cpp)

add_library(svm SHARED ${SOURCE_LIB})