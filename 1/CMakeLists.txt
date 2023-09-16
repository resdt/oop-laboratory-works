cmake_minimum_required(VERSION 3.27)

project(first-program-on-cpp)

# Build Google Test
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/../Google-Test"
    "googletest"
)

add_executable(
    main
    src/main.cpp
)
