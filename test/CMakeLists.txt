include_directories(${rl_SOURCE_DIR}/test/include)

add_subdirectory(src)

add_executable(testExecutable rl_testRunner.cpp)
target_link_libraries(testExecutable cppunit rlTest)