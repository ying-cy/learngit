cmake_minimum_required(VERSION 3.7.1)
 
project(AUX-test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2")
message("${CMAKE_C_FLAGS}")

add_executable(AUX-test test.c)
 
