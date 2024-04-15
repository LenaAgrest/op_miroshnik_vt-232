cmake_minimum_required(VERSION 3.26)
project(lab_14 C)

set(CMAKE_C_STANDARD 11)

include_directories(op_miroshnik_vt-232/libs/string)

add_executable(lab_14
        op_miroshnik_vt-232/libs/string/tasks/string_.c
        op_miroshnik_vt-232/libs/string/tasks/string_.h
        op_miroshnik_vt-232/libs/string/main.c)
