cmake_minimum_required(VERSION 3.5)

project(aldez LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(adlez
    src/main.cpp
    src/asefile.h
    src/asefileloader.h
    src/asefileloader.cpp
    src/contentloader.h
    src/contentloader.cpp
    src/entity.h
    src/entity.cpp
    src/game.h
    src/game.cpp
    src/graphics.h
    src/graphics.cpp
    src/map.h
    src/map.cpp
    src/point.h
    src/rectangle.h
    src/size.h
    src/sprite.h
    src/sprite.cpp
    src/spritebatch.h
    src/spritebatch.cpp
    src/texture.h
    src/texture.cpp

    src/testentity.h
    src/testentity.cpp
)
target_link_libraries(adlez
    ${SDL2_LIBRARIES}
    SDL2_image
    z
)

file(INSTALL
    ./content/block.png
    ./content/test.ase
    DESTINATION ./content)
