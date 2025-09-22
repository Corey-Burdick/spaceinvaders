cmake_minimum_required(VERSION 4.0)
project(tetris C CXX)

include_directories(include)

link_directories(lib)

set(MY_SOURCES
    src/main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} raylib)
