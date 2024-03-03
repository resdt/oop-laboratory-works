cmake_minimum_required(VERSION 3.10)
project(lab3)

enable_testing()

add_executable(lab3 main.cpp src/figure.cpp include/figure.h
                             src/rectangle.cpp include/rectangle.h
                             src/square.cpp include/square.h
                             src/trapezoid.cpp include/trapezoid.h
                             src/figure_array.cpp include/figure_array.h
)
target_include_directories(lab3 PRIVATE include)
set_target_properties(lab3 PROPERTIES OUTPUT_NAME "main")

add_executable(lab3_tests tests/tests.cpp src/figure.cpp include/figure.h
                             src/square.cpp include/square.h
                             src/trapezoid.cpp include/trapezoid.h
                             src/rectangle.cpp include/rectangle.h
                             src/figure_array.cpp include/figure_array.h
)

target_include_directories(lab3_tests PRIVATE include)
set_target_properties(lab3_tests PROPERTIES OUTPUT_NAME "tests")

target_link_libraries(
  lab3_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab3_tests)
