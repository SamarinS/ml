cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(cpm_svm)

set(SOURCE_LIB base.cpp  data.cpp  solve_qp.cpp  svm.cpp)

add_library(cpm_svm SHARED ${SOURCE_LIB})