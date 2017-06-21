cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(svm_test)

set(SOURCE_EXE main.cpp test.cpp)

add_executable(svm_test ${SOURCE_EXE})

target_link_libraries(svm_test svm)