cmake_minimum_required(VERSION 2.8.11)
project(rl)

include(CMakeFiles/CMakeLibraryCheck)
include(CMakeFiles/CMakePlatformCheck)
include(CMakeFiles/CMakeGenerateMainHeader)

set(intrinsic "none" CACHE STRING "The possible intrinsics are the following: none, mmx, sse, sse2, sse3, sse4, sse4.1, sse4.2, sse4a, avx.")

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)

# This is where the sub-headers will be installed in /usr/local/include directory.
set(SUB_HEADERS_PREFIX rl_bits)

# Include all header file to just one.
GenerateMainHeader(
        ${CMAKE_SOURCE_DIR}/include
        ${PROJECT_BINARY_DIR}
        ${SUB_HEADERS_PREFIX}
        ${CMAKE_SOURCE_DIR}/lib)
MESSAGE(STATUS "Generated global header file")

set(INSTALL_DIRECTORY /usr/local/include)
install(FILES ${PROJECT_BINARY_DIR}/rl
        DESTINATION ${INSTALL_DIRECTORY})
install(DIRECTORY ${PROJECT_BINARY_DIR}/${SUB_HEADERS_PREFIX}
        DESTINATION ${INSTALL_DIRECTORY}/${SUB_HEADERS_PREFIX})
