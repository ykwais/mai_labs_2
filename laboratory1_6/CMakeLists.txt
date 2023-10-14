cmake_minimum_required(VERSION 3.23)
project(laboratory1_6 C)

set(CMAKE_C_STANDARD 23)

add_library(MyLib functions.c)

add_executable(laboratory1_6 main.c enums.h)

target_link_libraries(laboratory1_6 MyLib)
