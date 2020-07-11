cmake_minimum_required (VERSION 3.6)

set(PROJECT_NAME HadesFCS)
project(${PROJECT_NAME})

add_subdirectory(Communication)
add_subdirectory(Firmware/F4Quad)
add_subdirectory(GPS)