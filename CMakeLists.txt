cmake_minimum_required(VERSION 3.3)
project(Contest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp getch.h GameObject.h Engine.h myGame.h)
add_executable(Contest ${SOURCE_FILES})