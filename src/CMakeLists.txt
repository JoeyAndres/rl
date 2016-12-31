include_directories(${CMAKE_SOURCE_DIR}/include)

# Intrinsic Sources.
add_subdirectory(agent)
add_subdirectory(coding)
add_subdirectory(hash)
add_subdirectory(db)

# Non-Intrinsic Sources.
add_library(rl
        # lib
        $<TARGET_OBJECTS:murmur3>
        $<TARGET_OBJECTS:superfasthash>
        $<TARGET_OBJECTS:unh>

        $<TARGET_OBJECTS:rlAgent>
        $<TARGET_OBJECTS:rlCodingContainer>
        $<TARGET_OBJECTS:rlHash>
        $<TARGET_OBJECTS:rlDB>)
target_link_libraries(rl ${PTHREAD_LIB})

if (ENABLE_DB STREQUAL "true")
    target_link_libraries(rl cassandra)
endif()

install(TARGETS rl DESTINATION lib)
