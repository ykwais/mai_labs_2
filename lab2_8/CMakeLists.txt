cmake_minimum_required(VERSION 3.23)
project(lab2_8 C)

set(CMAKE_C_STANDARD 23)

add_library(MyLib funcs.c)

add_executable(lab2_8 main.c helper.h)

target_link_libraries(lab2_8 MyLib)
