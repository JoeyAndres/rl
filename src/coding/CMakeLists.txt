include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_CODING_FILES "*.cpp")
add_library(rlCoding OBJECT ${SRC_CODING_FILES})
