cmake_minimum_required(VERSION 3.16)
project(highload2dz)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(highload2dz main.cpp src/server.cpp)

