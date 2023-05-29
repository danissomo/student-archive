cmake_minimum_required(VERSION 3.10)
project(DFP)
add_executable(app   main.c matrix_tricks.c dfp.c)
target_link_libraries(app m)