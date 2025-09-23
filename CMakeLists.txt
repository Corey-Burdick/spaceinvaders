cmake_minimum_required(VERSION 4.0)
project(SpaceInvaders C CXX)

include_directories(include)

link_directories(lib)

set(MY_SOURCES
    src/main.cpp
    src/game.cpp
    src/spaceship.cpp
    src/laser.cpp
    src/block.cpp
    src/obstacle.cpp
    src/alien.cpp
    src/mysteryship.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} raylib)
