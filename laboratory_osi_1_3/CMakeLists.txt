cmake_minimum_required(VERSION 3.23)
project(laboratory_osi_1_3 C)

set(CMAKE_C_STANDARD 23)

add_library(MyLib funsc.c)

add_executable(laboratory_osi_1_3 main.c enums.h)

target_link_libraries(laboratory_osi_1_3 MyLib)