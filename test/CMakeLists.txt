enable_testing()

add_executable(dummy-test dummy_test.cpp)
target_link_libraries(dummy-test libdummy)

target_link_options(dummy-test PRIVATE
    --specs=nosys.specs 
)

add_test(NAME dummy COMMAND dummy-test)