# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Name of your project
project(ConsoleGame)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set include path
include_directories(include)

# Automatically find all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Tell CMake to create an executable named "program" from those sources
add_executable(program ${SOURCES})

target_compile_options(program PRIVATE -g -fsanitize=address -fno-omit-frame-pointer)
target_link_options(program PRIVATE -fsanitize=address)