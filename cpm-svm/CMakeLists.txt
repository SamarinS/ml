cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

project(svm_all)

add_subdirectory(svm)
add_subdirectory(test)
add_subdirectory(python)
add_subdirectory(examples)