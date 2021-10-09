FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

include(GoogleTest)

add_executable(dummy-test ${CMAKE_CURRENT_SOURCE_DIR}/dummy_test.cpp)
target_link_libraries(dummy-test libdummy gtest gtest_main)
gtest_discover_tests(dummy-test)

add_executable(system-test ${CMAKE_CURRENT_SOURCE_DIR}/system_test.cpp)
target_link_libraries(system-test gtest gtest_main)
gtest_discover_tests(system-test)

add_executable(dummy-message-test ${CMAKE_CURRENT_SOURCE_DIR}/dummy_message_test.cpp)
target_link_libraries(dummy-message-test libdummy gtest gtest_main)
gtest_discover_tests(dummy-message-test)
