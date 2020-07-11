add_subdirectory(Device/ST/STM32F4xx)

add_library(cmsis INTERFACE)
target_include_directories(cmsis INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include)