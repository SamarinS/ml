cmake_minimum_required(VERSION 3.5)
project(python_svm_module)

set(SOURCE svmmodule.cpp)

add_library(svmmodule SHARED ${SOURCE})
set_target_properties(svmmodule PROPERTIES PREFIX "")

find_package(Python COMPONENTS Interpreter Development NumPy)

message("Python_FOUND:${Python_FOUND}")
message("Python_INCLUDE_DIRS:${Python_INCLUDE_DIRS}")
message("Python_NumPy_INCLUDE_DIRS:${Python_NumPy_INCLUDE_DIRS}")
message("Python_Development_FOUND:${Python_Development_FOUND}")
message("Python_LIBRARIES:${Python_LIBRARIES}")
if (Python_FOUND)
    include_directories(${Python_INCLUDE_DIRS})
    include_directories(${Python_NumPy_INCLUDE_DIRS})
    target_link_libraries(svmmodule ${Python_LIBRARIES})
endif(Python_FOUND)

target_link_libraries(svmmodule svm)
