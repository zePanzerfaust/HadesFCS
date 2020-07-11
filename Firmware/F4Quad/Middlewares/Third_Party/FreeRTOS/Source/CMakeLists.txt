set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_RTOS/cmsis_os.c
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang/heap_4.c
)

add_library(freertos ${SOURCES})

#target_link_libraries(freertos INTERFACE cmsis)

target_include_directories(freertos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Core/Inc)  # TODO: linking cmake library should resolve this?
target_include_directories(freertos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Drivers/CMSIS/Include)  # TODO: linking cmake library should resolve this?
target_include_directories(freertos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_RTOS)
target_include_directories(freertos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(freertos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F)