include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_ALGORITHM_GRADIENT_DESCENT_FILES "*.cpp")
add_library(rlAlgorithmGradientDescent OBJECT ${SRC_ALGORITHM_GRADIENT_DESCENT_FILES})
