cmake_minimum_required(VERSION 3.14)
project(Nightlock LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Nightlock
    kernel.cpp
)
target_link_libraries(Nightlock)