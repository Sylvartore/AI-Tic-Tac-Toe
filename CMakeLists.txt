cmake_minimum_required(VERSION 3.13)
project(ttt)

set(CMAKE_CXX_STANDARD 14)

add_executable(ttt main.cpp board.cpp board.hpp game.cpp game.hpp ai.cpp ai.hpp)