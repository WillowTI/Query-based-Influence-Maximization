cmake_minimum_required(VERSION 3.14)
project(sfmt)

set(CMAKE_CXX_STANDARD 14)

add_executable(sfmt main.cpp sfmt.h sfmt.cpp head.h Argument.h infgraph.h graph.h imm.h)