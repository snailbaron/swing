cmake_minimum_required(VERSION 3.8)

project(swing)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(deps)
add_subdirectory(src)

install (DIRECTORY res/ DESTINATION "data")
