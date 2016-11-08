include_directories(${rl_SOURCE_DIR}/include)
include_directories(${rl_SOURCE_DIR}/test/include)

# Sources
file(GLOB SRC_TEST_FILES "*.cpp")
add_library(rlTest ${SRC_TEST_FILES})
target_link_libraries(rlTest rl cppunit)