include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_DB_FILES "*.cpp")
add_library(rlDB OBJECT ${SRC_DB_FILES})
