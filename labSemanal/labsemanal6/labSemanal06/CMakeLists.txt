cmake_minimum_required(VERSION 3.5)
project(labSemanal06)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -lm")

set(SOURCE_FILES main.c)
add_executable(labSemanal06 ${SOURCE_FILES})
target_link_libraries(labSemanal06 m)