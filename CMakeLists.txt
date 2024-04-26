cmake_minimum_required(VERSION 3.22)
project(proyecto)
add_executable(proyecto main.cpp)

include_directories(/sqlite)
link_directories(/sqlite)
find_package(SqliteOrm REQUIRED)

target_link_libraries(proyecto PRIVATE sqlite_orm::sqlite_orm)