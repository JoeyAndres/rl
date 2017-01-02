include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_CODING_CONTAINER_FILES "*.cpp")
add_library(rlCodingContainer OBJECT ${SRC_CODING_CONTAINER_FILES})
