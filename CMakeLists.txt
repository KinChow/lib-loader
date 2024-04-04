cmake_minimum_required(VERSION 3.20)

if (NOT DEFINED MASTER_PROJECT)
    set(MASTER_PROJECT OFF)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(MASTER_PROJECT ON)
        message(STATUS "CMake version: ${CMAKE_VERSION}")
    endif()
endif()

project(LibLoader VERSION 1.0.0 LANGUAGES CXX)

option(ENABLE_EXAMPLE "Enable examples of LibLoader." ${MASTER_PROJECT})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if (ENABLE_EXAMPLE)
    add_subdirectory(examples)
    message(STATUS "Building examples done")
endif()
