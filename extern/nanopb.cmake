FetchContent_Declare(
    nanopb
    GIT_REPOSITORY https://github.com/nanopb/nanopb.git
    GIT_TAG        0.4.5
)
FetchContent_MakeAvailable(nanopb)
FetchContent_GetProperties(nanopb)
if(NOT nanopb_POPULATED)
    FetchContent_Populate(nanopb)
    add_subdirectory(${nanopb_SOURCE_DIR} ${nanopb_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
