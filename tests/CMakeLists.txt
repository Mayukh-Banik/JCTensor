# add_subdirectory(CPU)
# add_subdirectory(CUDA)
# add_subdirectory(HIP)

file(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
    # "*.cu"
)

# project(tests LANGUAGES CXX CUDA)
project(tests LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest
    gtest_main
    JCTensor
)