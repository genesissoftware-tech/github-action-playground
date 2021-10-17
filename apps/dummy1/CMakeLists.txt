cmake_minimum_required(VERSION 3.18)

# Project name and a few useful settings. Other commands can pick up the results
project(
  Dummy1
  VERSION 0.0.1
  DESCRIPTION "Dummy1 project"
  LANGUAGES CXX C ASM)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CROSSCOMPILE OFF CACHE BOOL "is crosscompiled")
    message(STATUS "CMAKE_CROSSCOMPILE ${CMAKE_CROSSCOMPILE}")

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
    include(FetchContent)
endif()

include(${CMAKE_SOURCE_DIR}/cmake/utils.cmake)

set(PROCESSORs STM32F407VG STM32F407ZG)

foreach(PROCESSOR IN LISTS PROCESSORs)
    set(EXECUTABLE ${PROJECT_NAME}_${PROCESSOR})
    add_executable(${EXECUTABLE})

    list(APPEND MCU
        -mthumb 
        -mcpu=cortex-m4+nofp
        -mfpu=fpv4-sp-d16
        -mfloat-abi=softfp
    )

    target_include_directories(${EXECUTABLE} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
    )

    target_sources(${EXECUTABLE} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROCESSOR}/startup.s
    )


    target_compile_options(${EXECUTABLE} PRIVATE
        ${MCU}
        -ffunction-sections
        -fdata-sections
    )
    target_link_options(${EXECUTABLE} PRIVATE
        ${MCU}
        --specs=nosys.specs 
        -Wl,--gc-sections
        -Wl,-Map=${EXECUTABLE}.map,--cref
        -T${CMAKE_CURRENT_SOURCE_DIR}/${PROCESSOR}/linker.ld
    )

    target_link_libraries(${EXECUTABLE} PRIVATE
        c
        m
        nosys
        libdummy
    )

    firmware_size(${EXECUTABLE})
    generate_object(${EXECUTABLE} .bin binary)

    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
        generate_object(${EXECUTABLE} .hex ihex)
    endif()

endforeach()
