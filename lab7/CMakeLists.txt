cmake_minimum_required(VERSION 3.10)
project(lab7)

enable_testing()

add_executable(lab7 main.cpp include/npc.h src/npc.cpp include/rogue.h src/rogue.cpp 
              include/bear.h src/bear.cpp include/elf_.h src/elf_.cpp include/factory.h src/factory.cpp
              include/observer.h src/observer.cpp
              )

target_include_directories(lab7 PRIVATE include)
set_target_properties(lab7 PROPERTIES OUTPUT_NAME "main")

add_executable(lab7_tests tests/tests.cpp include/npc.h src/npc.cpp include/rogue.h src/rogue.cpp 
              include/bear.h src/bear.cpp include/elf_.h src/elf_.cpp include/factory.h src/factory.cpp
              include/observer.h src/observer.cpp
              )

target_include_directories(lab7_tests PRIVATE include)
set_target_properties(lab7_tests PROPERTIES OUTPUT_NAME "tests")

target_link_libraries(
  lab7_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab7_tests)
