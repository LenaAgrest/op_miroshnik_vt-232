cmake_minimum_required(VERSION 3.10)
project(lr14)

set(CMAKE_C_STANDARD 11)

# add the executable
add_executable(
        main.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vector/vector.c
        libs/data_structures/vector/test.c
        libs/data_structures/vector/test.h
        libs/data_structures/vector/vectorVoid.c
        libs/data_structures/vector/vectorVoid.h

)