cmake_minimum_required(VERSION 3.16)
PROJECT(fmttest)

set(CMAKE_CXX_STANDARD 17)

SET(SRC_LIST test.cpp)


include_directories(/home/yilia/桌面/CMKAE-PRACTICE/fmt-test/include/fmt)

link_directories(
        ./
)
link_libraries(
        fmt
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


ADD_EXECUTABLE(fmttest ${SRC_LIST})
