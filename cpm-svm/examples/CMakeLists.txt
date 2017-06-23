cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_EXE main.cpp)

add_executable(svm-train-and-score ${SOURCE_EXE})

target_link_libraries(svm-train-and-score svm)