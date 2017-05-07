file (GLOB sources "*.cpp")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${src_SOURCE_DIR})
include_directories(${cpp-util_SOURCE_DIR}/include)

add_executable(tetris ${sources})
target_link_libraries(tetris ${Boost_LIBRARIES})
target_link_libraries(tetris cpp-util)
target_link_libraries(tetris src)
target_link_libraries(tetris Threads::Threads)
