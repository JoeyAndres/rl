include_directories(${CMAKE_SOURCE_DIR}/test/lib)
include_directories(${CMAKE_SOURCE_DIR}/test/helper/include)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(helper)

# We can't have "add_subdirectory(src)" since catch.hp requires everything to be compiled with each other, not linked.
file(GLOB_RECURSE SRC_TEST_FILES "src/*.cpp")

add_executable(testRunner testRunner.cpp ${SRC_TEST_FILES})
target_link_libraries(testRunner rlTestHelper)
