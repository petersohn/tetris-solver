file (GLOB sources "*.cpp")

add_executable(tetris ${sources})
target_link_libraries(tetris ${Boost_LIBRARIES})
target_link_libraries(tetris cpp-util)
target_link_libraries(tetris src)

