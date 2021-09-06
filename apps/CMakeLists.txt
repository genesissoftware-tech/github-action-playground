include(${CMAKE_SOURCE_DIR}/cmake/utils.cmake)

add_executable(${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f407zg_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f407zg_startup.s
)


target_compile_options(${PROJECT_NAME} PRIVATE
    ${${PROJECT_NAME}_MCU}
    -ffunction-sections
    -fdata-sections
)
target_link_options(${PROJECT_NAME} PRIVATE
    ${${PROJECT_NAME}_MCU}
    --specs=nosys.specs 
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map,--cref
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    c
    m
    nosys
    libdummy
)

linker_script_add(${CMAKE_SOURCE_DIR}/stm32f407zg.ld)
firmware_size(${PROJECT_NAME})
generate_object(${PROJECT_NAME} .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(${PROJECT_NAME} .hex ihex)
endif()
