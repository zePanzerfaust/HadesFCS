set(ELF_FILE ${PROJECT_NAME}.elf)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/BMX055.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/KalmanRollPitch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/KalmanRollPitchYaw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/LowPassFilter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/MPRLS_SPI.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/PCA9685.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/PIController.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_timebase_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/system_stm32f4xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Startup/startup_stm32f405rgtx.s
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/../STM32F405RGTX_FLASH.ld)
#set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F405RGTX_RAM.ld)

add_executable(${ELF_FILE}
    ${SOURCES}
    ${LINKER_SCRIPT}
)

target_include_directories(${ELF_FILE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)

target_include_directories(${ELF_FILE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include)  # TODO: linking cmake library should resolve this?
target_include_directories(${ELF_FILE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Device/ST/STM32F4xx/Include)  # TODO: linking cmake library should resolve this?

target_link_libraries(${ELF_FILE} INTERFACE cmsis)
target_link_libraries(${ELF_FILE} INTERFACE cmsis_stm32f4xx)
target_link_libraries(${ELF_FILE} PRIVATE stm32f4xx_hal_driver)
target_link_libraries(${ELF_FILE} PRIVATE freertos)

target_compile_definitions(${ELF_FILE} PRIVATE STM32F405xx)
target_compile_definitions(${ELF_FILE} PRIVATE USE_HAL_DRIVER)

#set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -nostartfiles")  # comment out if __libc_init_array is used

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map,\"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map\"")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker --gc-sections")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker --print-gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    include(${CMAKE_CURRENT_SOURCE_DIR}/gcc_compiler_flags.cmake)
endif()

if (CMAKE_BUILD_TYPE EQUAL "Debug")
    target_compile_definitions(${ELF_FILE} PRIVATE DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
elseif (CMAKE_BUILD_TYPE EQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
endif (CMAKE_BUILD_TYPE EQUAL "Debug")

set(HEX_FILE ${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_NAME}.bin)
add_custom_command(TARGET ${ELF_FILE} POST_BUILD
        COMMENT "Building ${HEX_FILE}"
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${ELF_FILE}> ${HEX_FILE}
        COMMENT "Building ${BIN_FILE}"
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${ELF_FILE}> ${BIN_FILE})
add_custom_command(TARGET ${ELF_FILE} POST_BUILD
        COMMENT "Create listing of ${ELF_FILE}"
        COMMAND ${CMAKE_OBJDUMP} --source --all-headers --demangle --disassemble --line-numbers --wide $<TARGET_FILE:${ELF_FILE}> > "${PROJECT_NAME}.lst")
add_custom_command(TARGET ${ELF_FILE} POST_BUILD
        COMMENT "Printing size of ${ELF_FILE}"
        COMMAND ${CMAKE_SIZE} --format=berkeley --totals  $<TARGET_FILE:${ELF_FILE}>)