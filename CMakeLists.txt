cmake_minimum_required(VERSION 3.16.3)
project(Triangle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

file(GLOB CPP_SOURCES "src/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})