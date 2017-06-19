cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(cpm_svm_test)

set(SOURCE_EXE main.cpp test.cpp)

add_executable(cpm_svm_test ${SOURCE_EXE})

target_link_libraries(cpm_svm_test cpm_svm)