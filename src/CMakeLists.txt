
include(${CMAKE_SOURCE_DIR}/extern/nanopb.cmake)

set(NANOPB_SRC_ROOT_FOLDER ${nanopb_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${NANOPB_SRC_ROOT_FOLDER}/extra)
find_package(Nanopb REQUIRED )

nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS 
    RELPATH ${CMAKE_SOURCE_DIR}/protos 
    ${CMAKE_SOURCE_DIR}/protos/dummy.proto)

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS}
    PROPERTIES GENERATED TRUE)

add_library(libdummy STATIC
    dummy.cpp
    ${PROTO_SRCS} ${PROTO_HDRS}
)

target_include_directories(libdummy PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${NANOPB_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)
