cmake_minimum_required(VERSION 3.23)
project(laboratory1_4 C)

set(CMAKE_C_STANDARD 23)

add_library(MyLib functions.c)

add_executable(laboratory1_4 main.c enum.h)

target_link_libraries(laboratory1_4 MyLib)