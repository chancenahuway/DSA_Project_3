cmake_minimum_required(VERSION 3.27)
project(DSA_Project_3)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SOURCE_FILES main.cpp)
add_executable(DSA_Project_3 ${SOURCE_FILES} main.cpp Maze.cpp Maze.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(DSA_Project_3 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)