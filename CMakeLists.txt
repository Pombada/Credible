cmake_minimum_required(VERSION 4.2)
project(Credible)

set(CMAKE_CXX_STANDARD 20)

add_executable(Credible main.cpp
        logic.h
        logic.cpp)
