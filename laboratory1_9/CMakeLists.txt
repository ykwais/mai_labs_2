cmake_minimum_required(VERSION 3.23)
project(laboratory1_9 C)

set(CMAKE_C_STANDARD 23)
add_library(MyLib funcs.c)

add_executable(laboratory1_9 main.c enum.h)

target_link_libraries(laboratory1_9 MyLib)
