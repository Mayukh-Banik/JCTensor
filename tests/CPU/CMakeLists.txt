file(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
)

project(CPUTests LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-g)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/Zi)
endif()

add_executable(CPUTests ${SOURCE_FILES})

target_link_libraries(CPUTests PRIVATE
    gtest
    gtest_main
    JCTensor
)