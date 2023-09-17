cmake_minimum_required(VERSION 3.27)

project(first-program-on-cpp)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#add_subdirectory(
#    "${CMAKE_CURRENT_SOURCE_DIR}/../Google-Test"
#    "googletest"
#)

# Main target
add_executable(
    main
    src/main.cpp
)

# Test target
add_executable(
    test-list
    test/test-list.cpp
)

# Add source to the include directories for the test target
target_include_directories(
    test-list PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target to gtest libraries
target_link_libraries(
    test-list PRIVATE
    gtest gtest_main
)
