cmake_minimum_required(VERSION 3.20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
set(OPENCL_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBLOADER_INTERFACE_HEADER_DIR ${EXECUTABLE_OUTPUT_PATH}/include)

include_directories(
    ${OPENCL_HEADER_DIR}
    ${LIBLOADER_INTERFACE_HEADER_DIR}
)

link_directories(
    ${EXECUTABLE_OUTPUT_PATH}
)

add_executable(example example.cpp)

target_link_libraries(example LibLoader)
