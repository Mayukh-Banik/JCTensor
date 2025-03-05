cmake_minimum_required(VERSION 3.28)

project(JCTensor)

option(ENABLE_TESTING "Enable testing" OFF)

add_subdirectory(JCTensor)

if(ENABLE_TESTING)
    add_subdirectory(googletest)
    add_subdirectory(tests)
endif()