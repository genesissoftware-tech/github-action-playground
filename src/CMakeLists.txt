add_library(libdummy STATIC
    dummy.cpp
)

target_include_directories(libdummy PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)