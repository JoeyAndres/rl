include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB SRC_HASH_FILES "*.cpp")
add_library(rlHash OBJECT ${SRC_HASH_FILES})
