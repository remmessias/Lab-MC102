cmake_minimum_required(VERSION 3.5)
project(labSemanal07)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -lm")

set(SOURCE_FILES main.c estrutura.c lista.c)
add_executable(labSemanal07 ${SOURCE_FILES})
