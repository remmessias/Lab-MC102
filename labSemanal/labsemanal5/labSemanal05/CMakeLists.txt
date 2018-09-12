cmake_minimum_required(VERSION 3.5)
project(labSemanal05)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -lm")

set(SOURCE_FILES labSemanal05.c)

add_executable(labSemanal05 ${SOURCE_FILES})