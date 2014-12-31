include_directories(${AIProject_SOURCE_DIR}/include)
include_directories(${AIProject_SOURCE_DIR}/test/include)

# Sources
file(GLOB SRC_TEST_FILES "*.cpp")
add_library(aiproject2Test ${SRC_TEST_FILES})
target_link_libraries(aiproject2Test aiproject2 cppunit)