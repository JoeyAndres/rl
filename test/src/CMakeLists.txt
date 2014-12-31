include_directories(${AIProject_SOURCE_DIR}/include)
include_directories(${AIProject_SOURCE_DIR}/test/include)

# Sources
file(GLOB SRC_FILES "*.cpp")
add_library(aiproject2Test ${SRC_FILES})