cmake_minimum_required(VERSION 3.15)
project(exe_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(exe_1
        main.c
        v1_parent.c
        v1_parent.h
        v2_parent.c
        v2_parent.h
        v2_child.c
        )
