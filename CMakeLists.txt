cmake_minimum_required(VERSION 3.28)

project(JCTensor)

option(ENABLE_TESTING "Enable testing" OFF)

add_subdirectory(JCTensor)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/CLBlast)

if(ENABLE_TESTING)
    add_subdirectory(extern/googletest)
    add_subdirectory(tests)
endif()

