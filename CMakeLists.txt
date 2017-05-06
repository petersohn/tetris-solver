cmake_minimum_required (VERSION 2.8.12.2)
project(tetris-solver)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

set (CXX_COMMON_FLAGS "-std=c++14 -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG "${CXX_COMMON_FLAGS} -O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "${CXX_COMMON_FLAGS} -O2")

set (turtle_dir ${CMAKE_SOURCE_DIR}/turtle)
set (turtle_include_dir ${turtle_dir}/include)

find_package(Boost COMPONENTS serialization filesystem program_options system unit_test_framework thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory (cpp-util)
add_subdirectory (bin)
add_subdirectory (src)
add_subdirectory (test)
