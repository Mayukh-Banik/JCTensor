cmake_minimum_required(VERSION 3.28)

add_library(JCTensor INTERFACE)

target_include_directories(JCTensor 
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

add_library(JCTensor::JCTensor ALIAS JCTensor)

find_package(OpenCL REQUIRED)

target_link_libraries(JCTensor INTERFACE ${OpenCL_LIBRARIES})
target_include_directories(JCTensor INTERFACE ${OpenCL_INCLUDE_DIRS})
target_link_directories(JCTensor INTERFACE ${clblast})
target_include_directories(JCTensor INTERFACE ${clblast}/include)