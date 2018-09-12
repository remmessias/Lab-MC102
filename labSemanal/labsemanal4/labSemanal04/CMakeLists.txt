cmake_minimum_required(VERSION 3.5)
project(labSemanal04)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -lm")

set(SOURCE_FILES labSemanal04.c)
add_executable(labSemanal04 ${SOURCE_FILES})