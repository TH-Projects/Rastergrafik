cmake_minimum_required(VERSION 3.24)
project(Rastergrafik C)

set(CMAKE_C_STANDARD 11)

add_executable(Rastergrafik main.c draw.c macros.h)
