include_directories(${rl_SOURCE_DIR}/include)

# Intrinsic Sources.
add_subdirectory(intrinsic)

# Non-Intrinsic Sources.
file(GLOB SRC_FILES "*.cpp")
add_library(rlNoIntrinsic OBJECT ${SRC_FILES})
add_library(rl $<TARGET_OBJECTS:rlIntrinsic> $<TARGET_OBJECTS:rlNoIntrinsic>)
target_link_libraries(rl ${ARMADILLO_LIB} ${PTHREAD_LIB})

install(TARGETS rl DESTINATION lib)
install(DIRECTORY ../include/ DESTINATION /usr/local/include/rl)
