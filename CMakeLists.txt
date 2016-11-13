cmake_minimum_required(VERSION 3.0.2)
project(rl)

include(CMakeFiles/CMakeLibraryCheck)
include(CMakeFiles/CMakePlatformCheck)
include(CMakeFiles/CMakeGenerateMainHeader)

set(intrinsic "none" CACHE STRING "The possible intrinsics are the following: none, mmx, sse, sse2, sse3, sse4, sse4.1, sse4.2, sse4a, avx.")

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O3 -g")

add_subdirectory(src)
add_subdirectory(test)

# This is where the sub-headers will be installed in /usr/local/include directory.
set(SUB_HEADERS_PREFIX rl_bits)

# Include all header file to just one.
GenerateMainHeader(${rl_SOURCE_DIR}/include ${PROJECT_BINARY_DIR} ${SUB_HEADERS_PREFIX})
MESSAGE(STATUS "Generated global header file")

install(FILES ${PROJECT_BINARY_DIR}/rl DESTINATION /usr/local/include/)
install(DIRECTORY ${rl_SOURCE_DIR}/include/ DESTINATION /usr/local/include/${SUB_HEADERS_PREFIX})
