include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test/lib)
include_directories(${CMAKE_SOURCE_DIR}/test/helper/include)

# Sources
file(GLOB SRC_TEST_HELPER_FILES "*.cpp")
add_library(rlTestHelper ${SRC_TEST_HELPER_FILES})
target_link_libraries(rlTestHelper rl)
