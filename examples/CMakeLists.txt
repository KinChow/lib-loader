cmake_minimum_required(VERSION 3.20)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(./include)

add_executable(example example.cpp)

target_link_libraries(example LibLoader)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
