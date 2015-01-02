cmake_minimum_required(VERSION 2.8)
project(AIProject)

set(intrinsic "none" CACHE STRING "The possible intrinsics are the following: none, mmx, sse, sse2, sse3, sse4, sse4.1, sse4.2, sse4a, avx.")

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -O3")

add_subdirectory(src)
add_subdirectory(test)