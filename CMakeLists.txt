cmake_minimum_required(VERSION 3.0...4.0)
project(SpaceInvaders C CXX)

include(FetchContent)

set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

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

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)
