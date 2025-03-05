file(GLOB_RECURSE SOURCE_FILES
    "*.cu"
)

project(CUDATests LANGUAGES CUDA)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#   add_compile_options(-g)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#   add_compile_options(/Zi)
endif()

add_executable(CUDATests ${SOURCE_FILES})

add_compile_options(--debug --device-debug --generate-line-info)

target_link_libraries(CUDATests PRIVATE
    gtest
    gtest_main
    JCTensor
)