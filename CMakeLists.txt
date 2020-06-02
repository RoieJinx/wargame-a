cmake_minimum_required(VERSION 3.16)
project(WatGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(WatGame Board.hpp  Board.cpp Soldier.hpp FootSoldier.cpp Soldier.cpp  Demo.cpp DemoGame.hpp DemoGame.cpp )