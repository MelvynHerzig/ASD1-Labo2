cmake_minimum_required(VERSION 3.15)
project(Labo2)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic")

set(CMAKE_CXX_STANDARD 11)

add_executable(Labo2 main.cpp Pieces.cpp Pieces.h)