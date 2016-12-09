include_directories(${CMAKE_SOURCE_DIR}/include)

# Intrinsic Sources.
add_subdirectory(agent)
add_subdirectory(hash)

# Non-Intrinsic Sources.
add_library(rl
        # lib
        $<TARGET_OBJECTS:murmur3>
        $<TARGET_OBJECTS:superfasthash>
        $<TARGET_OBJECTS:unh>

        $<TARGET_OBJECTS:rlAgent>
        $<TARGET_OBJECTS:rlHash>)
target_link_libraries(rl ${PTHREAD_LIB})

install(TARGETS rl DESTINATION lib)
