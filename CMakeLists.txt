cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)

project(freertos-mem)

# Set a default build type if none was specified
set(default_build_type "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

file(GLOB FREERTOS_SRC_FILES ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/*.c)

add_executable(main
    ${CMAKE_SOURCE_DIR}/test_pthread_suspension_dur.cpp
    ${FREERTOS_SRC_FILES}
    ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/portable/MemMang/heap_3.c
    ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/port.c
    ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
    ${FREERTOS_TRACE_SRC_FILES}
)

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/include
    ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix
    ${CMAKE_SOURCE_DIR}/FreeRTOS/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils
)
