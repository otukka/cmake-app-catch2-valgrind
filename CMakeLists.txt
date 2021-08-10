cmake_minimum_required(VERSION 3.16)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(app VERSION 1.0.0)

add_executable(app)

target_sources(app 
PRIVATE
    src/main.cpp
    src/Container.cpp
    src/Shared.cpp
)
target_include_directories(app PRIVATE src)

