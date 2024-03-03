cmake_minimum_required(VERSION 3.10)
project(lab2)

enable_testing()

add_executable(lab2 main.cpp src/money.cpp include/money.h)
target_include_directories(lab2 PRIVATE include)
set_target_properties(lab2 PROPERTIES OUTPUT_NAME "main")

add_executable(lab2_tests tests/tests.cpp src/money.cpp include/money.h)
target_include_directories(lab2_tests PRIVATE include)
set_target_properties(lab2_tests PROPERTIES OUTPUT_NAME "tests")

target_link_libraries(
  lab2_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab2_tests)
