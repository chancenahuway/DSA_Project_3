cmake_minimum_required(VERSION 3.27)
project(LearnSFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearnSFML main.cpp
        TextureManager.h
        TextureManager.cpp
        Maze.cpp
        Tile.h
        Tile.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)


include_directories(C:/SFML-2.6.1/lib/cmake/SFML)
target_link_libraries(LearnSFML sfml-system sfml-window sfml-graphics sfml-audio)
