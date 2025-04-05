cmake_minimum_required(VERSION 3.30)
project(app1 C)

set(CMAKE_C_STANDARD 11)

add_executable(app1 main.c
        orders.h
        csv_reader.h
        csv_reader.c
        metrics.c
        metrics.h)
