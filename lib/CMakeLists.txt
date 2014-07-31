if(NOT DEFINED PROJECT_NAME)
    project(libmarlight)
    cmake_minimum_required(VERSION 2.8)

    # C++ options
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

include_directories(.)
include_directories(..)

file(GLOB_RECURSE LIB_SOURCES "*.cpp" "*.c")
file(GLOB_RECURSE LIB_HEADERS "*.h" "*.hpp")

set(LIB_TARGET marlight)

#include_directories(${Boost_INCLUDE_DIRS})

add_library(${LIB_TARGET} SHARED ${LIB_SOURCES})

set_target_properties(${LIB_TARGET} PROPERTIES VERSION "0.1.0" SOVERSION "0")

#target_link_libraries(${CM_TARGET})
