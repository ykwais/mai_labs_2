cmake_minimum_required(VERSION 3.23)
project(lab2_1 C)

set(CMAKE_C_STANDARD 23)

add_library(MyLib funcs.c)

add_executable(lab2_1 main.c helper.h funcs.c)

target_link_libraries(lab2_1 MyLib)
