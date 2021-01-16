cmake_minimum_required(VERSION 3.5)

project(myzeldanes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(myzeldanes
    src/main.cpp
    src/game.h
    src/game.cpp
    src/graphics.h
    src/graphics.cpp
    src/map.h
    src/map.cpp
    src/spritebatch.h
    src/spritebatch.cpp
)
target_link_libraries(myzeldanes ${SDL2_LIBRARIES})
