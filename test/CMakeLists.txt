
add_executable(dummy-test dummy_test.cpp)
target_link_libraries(dummy-test libdummy)

add_test(NAME dummy COMMAND dummy-test)