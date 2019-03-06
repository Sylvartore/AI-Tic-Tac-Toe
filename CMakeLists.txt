cmake_minimum_required(VERSION 3.13)
project(tic-tac-toe-ai)

set(CMAKE_CXX_STANDARD 14)

add_executable(tic-tac-toe-ai main.cpp board.cpp board.hpp game.cpp game.hpp ai.cpp ai.hpp)