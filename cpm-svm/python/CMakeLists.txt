cmake_minimum_required(VERSION 3.1)
project(spam)

set(SOURCE spammodule.cpp)

add_library(spam SHARED ${SOURCE})
set_target_properties(spam PROPERTIES PREFIX "")

find_package(PythonLibs 2.7 REQUIRED)
if (PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(spam ${PYTHON_LIBRARIES})
endif(PYTHONLIBS_FOUND)

target_link_libraries(spam svm)
