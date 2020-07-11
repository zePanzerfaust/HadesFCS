cmake_minimum_required (VERSION 3.6)
set(PROJECT_NAME GPSNMEAParser)

project (${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 99)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/GPSNMEAParser.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})