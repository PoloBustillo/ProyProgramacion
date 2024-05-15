cmake_minimum_required(VERSION 3.22)
project(proyecto)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyecto src/main.cpp src/sqlite/sqlite3.c)


