cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(cpm_svm_all)

add_subdirectory(cpm-svm)
add_subdirectory(test)
add_subdirectory(python)