cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(svm)

set(SOURCE_LIB base.cpp data.cpp dense_data.cpp sparse_data.cpp
    solve_qp.cpp svm.cpp)

add_library(svm SHARED ${SOURCE_LIB})