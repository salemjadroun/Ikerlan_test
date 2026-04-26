cmake_minimum_required(VERSION 3.10)
project(set_1 C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS include/*.h)

add_executable(main ${SOURCES} ${HEADERS})
target_include_directories(main PRIVATE include)