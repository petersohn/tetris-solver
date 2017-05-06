file (GLOB sources *.cpp)

include_directories(${src_SOURCE_DIR})
include_directories(${cpp-util_SOURCE_DIR}/include)

add_executable(tetris-test ${sources})
target_link_libraries(tetris-test ${Boost_LIBRARIES})
target_link_libraries(tetris-test ${src_LIBRARIES})
