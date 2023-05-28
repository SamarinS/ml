cmake_minimum_required(VERSION 3.1)
project(python_svm_module)

set(SOURCE svmmodule.cpp)

add_library(svmmodule SHARED ${SOURCE})
set_target_properties(svmmodule PROPERTIES PREFIX "")

find_package(PythonLibs 3.1 REQUIRED)
if (PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(svmmodule ${PYTHON_LIBRARIES})
endif(PYTHONLIBS_FOUND)

target_link_libraries(svmmodule svm)
