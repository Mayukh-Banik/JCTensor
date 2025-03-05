cmake_minimum_required(VERSION 3.28)

add_library(JCTensor INTERFACE)

target_include_directories(JCTensor 
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

add_library(JCTensor::JCTensor ALIAS JCTensor)