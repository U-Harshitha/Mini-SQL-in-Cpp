cmake_minimum_required(VERSION 3.16)
project(MiniDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(minidb
    src/main.cpp
    src/parser.cpp
    src/table.cpp
)

target_include_directories(minidb PRIVATE include)
