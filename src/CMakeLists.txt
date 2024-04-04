cmake_minimum_required(VERSION 3.20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

aux_source_directory(. DIR_SRCS)

add_library(LibLoader STATIC ${DIR_SRCS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

file(GLOB allCopyFiles  "${CMAKE_CURRENT_SOURCE_DIR}/../include/*")
file(COPY ${allCopyFiles} DESTINATION ${LIBRARY_OUTPUT_PATH})
