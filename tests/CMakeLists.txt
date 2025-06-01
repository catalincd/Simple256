add_executable(simple256_tests 
    utils.cpp
    integration_tests.cpp
    unit_tests.cpp)
target_link_libraries(simple256_tests gtest_main simple256)

include(GoogleTest)
gtest_discover_tests(simple256_tests)
