set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_cortex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_dma.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_dma_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_exti.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_flash.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_flash_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_flash_ramfunc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_gpio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_i2c.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_i2c_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_pwr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_pwr_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_rcc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_rcc_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_spi.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_tim.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_tim_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32f4xx_hal_uart.c
)

add_library(stm32f4xx_hal_driver ${SOURCES})

target_compile_definitions(stm32f4xx_hal_driver PRIVATE STM32F405xx)

#target_link_libraries(stm32f4xx_hal_driver INTERFACE cmsis)
#target_link_libraries(stm32f4xx_hal_driver INTERFACE cmsis_stm32f4xx)

target_include_directories(stm32f4xx_hal_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc)  # TODO: linking cmake library should resolve this?
target_include_directories(stm32f4xx_hal_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include)  # TODO: linking cmake library should resolve this?
target_include_directories(stm32f4xx_hal_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32F4xx/Include)  # TODO: linking cmake library should resolve this?
target_include_directories(stm32f4xx_hal_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_include_directories(stm32f4xx_hal_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc/Legacy)