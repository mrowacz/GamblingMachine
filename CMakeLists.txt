cmake_minimum_required(VERSION 3.5.1)

option(test "Build all tests." ON) # Makes boolean 'test' available.

project(GamblingMachine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

find_package(Boost COMPONENTS system REQUIRED)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(gm ${SOURCE_FILES})
