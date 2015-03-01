include_directories(${AIProject_SOURCE_DIR}/include)

# Intrinsic Sources.
add_subdirectory(intrinsic)

# Non-Intrinsic Sources.
file(GLOB SRC_FILES "*.cpp")
add_library(aiproject2NoIntrinsic OBJECT ${SRC_FILES})
add_library(aiproject2 $<TARGET_OBJECTS:aiproject2Intrinsic> $<TARGET_OBJECTS:aiproject2NoIntrinsic>)
target_link_libraries(aiproject2 armadillo pthread)