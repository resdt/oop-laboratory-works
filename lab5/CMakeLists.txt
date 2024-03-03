cmake_minimum_required(VERSION 3.10)
project(lab5)

enable_testing()

add_executable(lab5 main.cpp include/allocator.h include/vector.h
)

target_include_directories(lab5 PRIVATE include)
set_target_properties(lab5 PROPERTIES OUTPUT_NAME "main")

add_executable(lab5_tests tests/tests.cpp include/allocator.h include/vector.h
)

target_include_directories(lab5_tests PRIVATE include)
set_target_properties(lab5_tests PROPERTIES OUTPUT_NAME "tests")

target_link_libraries(
  lab5_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab5_tests)
