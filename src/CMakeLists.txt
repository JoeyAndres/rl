include_directories(${AIProject_SOURCE_DIR}/include)

# Intrinsic Sources.
add_subdirectory(intrinsic)

# Non-Intrinsic Sources.
file(GLOB SRC_FILES "*.cpp")
add_library(aiproject2NoIntrinsic OBJECT ${SRC_FILES})