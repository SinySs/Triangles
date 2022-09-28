cmake_minimum_required(VERSION 3.16.3)

project(GoogleTest)

add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
include_directories(../include)
set(SOURCE_FILE unit_tests.cpp ../src/triangles.cpp)

add_executable(GoogleTest ${SOURCE_FILE})

target_link_libraries(GoogleTest gtest)