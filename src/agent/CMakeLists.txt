include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_AGENT_FILES "*.cpp")
add_library(rlAgent OBJECT ${SRC_AGENT_FILES})
