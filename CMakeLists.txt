cmake_minimum_required(VERSION 3.9)
project(malloc)

set(CMAKE_CXX_STANDARD 11)

add_executable(malloc
        incl/malloc.h
        src/allocator.c
        src/calloc.c
        src/find_block.c
        src/free.c
        src/malloc.c
        src/optimize.c
        src/realloc.c
        src/show_alloc_mem.c
        src/struct_init.c
        main.c)
