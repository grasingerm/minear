cmake_minimum_required(VERSION 2.8)

project(minear)

# compiler flags
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -std=c++11 -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -g -std=c++11 -pedantic -pedantic-errors -O3")

# build directories
set(CMAKE_BINARY_DIR build)
set(EXECUTABLE_OUTPUT_PATH bin)

# dependencies
add_executable(base base.cpp)
add_executable(memory memory.cpp)
add_executable(main main.cpp)

include_directories(../src)

target_link_libraries(base armadillo)

install(TARGETS base memory DESTINATION bin)

