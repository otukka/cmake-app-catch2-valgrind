cmake_minimum_required(VERSION 3.16)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(app VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(app)

target_sources(app PRIVATE
src/main.cpp
)
target_include_directories(app PRIVATE src)

target_compile_options(app PRIVATE -Wpedantic -Wextra -Werror)

add_subdirectory(Catch2)
add_executable(tests)

target_sources(tests PRIVATE
tests/main.cpp
)

target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Catch2/contrib/")



include(CTest)
include(Catch)
catch_discover_tests(tests)