project(marlight)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(lib)

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME}-cli ${SRC_LIST})

