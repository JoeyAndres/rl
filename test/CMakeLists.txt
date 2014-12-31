include_directories(${AIProject_SOURCE_DIR}/test/include)

add_subdirectory(src)

add_executable(test AIProject_testRunner.cpp)
target_link_libraries(test cppunit armadillo pthread boost_system aiproject2Test)