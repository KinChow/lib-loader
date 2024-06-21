cmake_minimum_required(VERSION 3.20)

set(OPENCL_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBLOADER_INTERFACE_HEADER_DIR ${EXECUTABLE_OUTPUT_PATH}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
include_directories(
    ${OPENCL_HEADER_DIR}
    ${LIBLOADER_INTERFACE_HEADER_DIR}
)
link_directories(
    ${EXECUTABLE_OUTPUT_PATH}
)
add_executable(example example.cpp)
target_link_libraries(example ${PROJECT_NAME})
