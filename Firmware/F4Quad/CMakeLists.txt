cmake_minimum_required (VERSION 3.6)
set(PROJECT_NAME F4QUAD)

project (${PROJECT_NAME} C ASM)
set(CMAKE_C_STANDARD 99)

#MESSAGE( STATUS "SOURCE: " ${SOURCE} )
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(Core)
add_subdirectory(Drivers)
add_subdirectory(Middlewares)