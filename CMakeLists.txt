cmake_minimum_required(VERSION 3.6)
project(ControlMI_PMIK C ASM)

#####
# CHANGE HERE
SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F303ZETx_FLASH.ld)
SET(COMMON_FLAGS "-O3 -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -fno-builtin -ffunction-sections -fdata-sections -gdwarf-2 -g -fno-common -fmessage-length=0")
#####

set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
SET(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -T ${LINKER_SCRIPT}")

file(GLOB_RECURSE USER_SOURCES "Src/*.c")

#####
# CHANGE HERE
file(GLOB_RECURSE HAL_SOURCES "Drivers/STM32F3xx_HAL_Driver/Src/*.c")
file(GLOB_RECURSE USB_SOURCES "Middlewares/ST/STM32_USB_Device_Library/Core/Src/*.c")
file(GLOB_RECURSE USB_CLASS_SOURCES "Middlewares/MIDI/Src/*.c")
add_library(CMSIS Drivers/CMSIS/Device/ST/STM32F3xx/Source/Templates/gcc/startup_stm32f303xe.s)
#####

include_directories(Inc)
include_directories(Drivers/CMSIS/Include)
#####
# CHANGE HERE
include_directories(Drivers/STM32F3xx_HAL_Driver/Inc)
include_directories(Middlewares/ST/STM32_USB_Device_Library/Core/Inc)
include_directories(Middlewares/MIDI/Inc)
include_directories(Drivers/CMSIS/Device/ST/STM32F3xx/Include)
include_directories(usr/lib/arm-none-eabi/include)
#####

add_executable(${PROJECT_NAME}.elf ${HAL_SOURCES} ${USB_SOURCES} ${USB_CLASS_SOURCES} ${USER_SOURCES}  ${LINKER_SCRIPT})

target_link_libraries(${PROJECT_NAME}.elf CMSIS)
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE STM32F303xE)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map")
set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)
set(ELF_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.elf)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMAND echo Sections:
        COMMAND readelf -S $<TARGET_FILE:${PROJECT_NAME}.elf> | grep 'Name\\|isr\\|text\\|bss\\|data\\|array'
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
