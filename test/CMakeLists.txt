include_directories(${AIProject_SOURCE_DIR}/test/include)

add_subdirectory(src)

add_executable(testExecutable AIProject_testRunner.cpp)
target_link_libraries(testExecutable cppunit aiproject2Test)