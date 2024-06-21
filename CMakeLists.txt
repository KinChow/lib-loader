cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "LibLoader")
project(${PROJECT_NAME})

set(DEBUG_VERSION "DebugMode")
set(RELEASE_VERSION "ReleaseMode")
set(COMPILE_MODE ${DEBUG_VERSION})
# debug mode (project name + compile time)
if(${COMPILE_MODE} MATCHES ${DEBUG_VERSION})
    set(USE_RELEASE_MODE 0)
    set(CMAKE_BUILD_TYPE "Debug")
# release mode (project name + version)
else()
    set(USE_RELEASE_MODE 1)
    set(CMAKE_BUILD_TYPE "Release")
endif()

string(TIMESTAMP COMPILE_TIME %y%m%d_%H%M%S)
set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_TWEAK 2)

set(CMAKE_CXX_STANDARD 17)

set(LIBLOADER_INTERNAL_HEADER_DIR ${PROJECT_SOURCE_DIR}/internal)
set(LIBLOADER_INTERFACE_HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src LIBLOADER_SRC_DIR)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(BUILD_LIBRARY ON)
else()
    set(BUILD_LIBRARY OFF)
endif()

if (BUILD_LIBRARY)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
    include_directories(
        ${LIBLOADER_INTERNAL_HEADER_DIR}
        ${LIBLOADER_INTERFACE_HEADER_DIR}
    )
    add_library(${PROJECT_NAME} STATIC ${LIBLOADER_SRC_DIR})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIBLOADER_INTERFACE_HEADER_DIR} ${LIBRARY_OUTPUT_PATH}/include
    )

    option(ENABLE_EXAMPLE "Enable examples of LibLoader." OFF)
    if (ENABLE_EXAMPLE)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
    endif()
else()
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME} INTERFACE ${LIBLOADER_INTERFACE_HEADER_DIR} ${LIBLOADER_INTERNAL_HEADER_DIR})
    target_sources(${PROJECT_NAME} INTERFACE ${LIBLOADER_SRC_DIR})
endif()
