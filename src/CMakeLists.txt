project(src)

file (GLOB sources "*.cpp")

include_directories(${cpp-util_SOURCE_DIR}/include)

add_library(src ${sources})
