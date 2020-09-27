INCLUDE(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)
#SET(CMAKE_SYSTEM_VERSION 1)
#SET(CMAKE_CROSSCOMPILING TRUE)

if(NOT DEFINED CROSS_COMPILER_TOOLCHAIN_DIR)
    message(FATAL_ERROR "Variable CROSS_COMPILER_TOOLCHAIN_DIR is not set. Point it to the directory where gcc can be found.")
endif()

SET(COMPILER_POSTFIX )
if(WIN32)
    SET(COMPILER_POSTFIX .exe)
endif(WIN32)

SET(CROSS_COMPILER_PREFIX arm-none-eabi-)

#SET(CMAKE_ASM_COMPILER ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}gcc${COMPILER_POSTFIX})
SET(CMAKE_C_COMPILER   ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}gcc${COMPILER_POSTFIX})
SET(CMAKE_CXX_COMPILER ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}g++${COMPILER_POSTFIX})
SET(CMAKE_LINKER       ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}ld${COMPILER_POSTFIX})
#SET(CMAKE_AR           ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}ar${COMPILER_POSTFIX})
SET(CMAKE_OBJCOPY      ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}objcopy${COMPILER_POSTFIX})
SET(CMAKE_OBJDUMP      ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}objdump${COMPILER_POSTFIX})
SET(CMAKE_SIZE         ${CROSS_COMPILER_TOOLCHAIN_DIR}/${CROSS_COMPILER_PREFIX}size${COMPILER_POSTFIX})

# CLion refused to generate valid files without this (could not compile ...)
set(CMAKE_C_COMPILER_ID       GNU)
set(CMAKE_CXX_COMPILER_ID     GNU)
set(CMAKE_C_COMPILER_FORCED   TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

# search for programs in the build host directories
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)  # linker error because of startup code
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# CPU relevant flags
# placed here so that all libraries and projects use the same CPU architecture
# else for example there is problems because the arm instruction set is used by
# default, which leads to compile errors when compiling assembly
set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -mlittle-endian")
set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -mcpu=cortex-m4")
set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -march=armv7e-m")
set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -mfloat-abi=hard")
set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -mfpu=fpv4-sp-d16")
set(CMAKE_COMMON_FLAGS "${CMAKE_COMMON_FLAGS} -mthumb")

# cache the flags for use
#MESSAGE(STATUS "FLAGS: " ${CMAKE_COMMON_FLAGS} )
set(CMAKE_C_FLAGS   "${CMAKE_COMMON_FLAGS}" CACHE STRING "CFLAGS")
set(CMAKE_CXX_FLAGS "${CMAKE_COMMON_FLAGS}" CACHE STRING "CXXFLAGS")
set(CMAKE_ASM_FLAGS "${CMAKE_COMMON_FLAGS}" CACHE STRING "")