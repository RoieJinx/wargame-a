cmake_minimum_required(VERSION 3.16)
project(WatGame)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(my_app Threads::Threads)
add_executable(WatGame Board.hpp DemoGame.cpp DemoGame.hpp TestCounter.cpp Demo.cpp Board.cpp Soldier.hpp FootSoldier.cpp Soldier.cpp FootCommander.cpp Sniper.cpp SniperCommander.cpp Paramedic.cpp ParamedicCommander.cpp ParamedicCommander.hpp doctest.h)