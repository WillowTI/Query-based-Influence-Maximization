cmake_minimum_required(VERSION 3.14)
project(fuck)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(fuck
        Argument.h
        graph.h
        head.h
        imm.h
        infgraph.h
        main.cpp
        sfmt.cpp
        sfmt.h)
