cmake_minimum_required(VERSION 3.10)
project(lab6)

enable_testing()

add_executable(lab6 main.cpp include/npc.h src/npc.cpp include/rogue.h src/rogue.cpp 
              include/bear.h src/bear.cpp include/elf_.h src/elf_.cpp include/observer.h src/observer.cpp 
              include/factory.h src/factory.cpp include/visitor.h src/visitor.cpp)

target_include_directories(lab6 PRIVATE include)
set_target_properties(lab6 PROPERTIES OUTPUT_NAME "main")

add_executable(lab6_tests tests/tests.cpp include/npc.h src/npc.cpp include/rogue.h src/rogue.cpp 
              include/bear.h src/bear.cpp include/elf_.h src/elf_.cpp include/observer.h src/observer.cpp 
              include/factory.h src/factory.cpp include/visitor.h src/visitor.cpp)

target_include_directories(lab6_tests PRIVATE include)
set_target_properties(lab6_tests PROPERTIES OUTPUT_NAME "tests")
target_link_libraries(
  lab6_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab6_tests)
