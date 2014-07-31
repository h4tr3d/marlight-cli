project(marlight)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(lib)

# C++ options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(lib)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME}-cli ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}-cli marlight)

