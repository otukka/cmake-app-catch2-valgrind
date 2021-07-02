cmake_minimum_required(VERSION 3.16)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(app VERSION 1.0.0)

add_executable(app)

target_sources(app PRIVATE
src/main.cpp
)
target_include_directories(app PRIVATE src)


add_subdirectory(Catch2)
add_executable(tests)

target_sources(tests PRIVATE
tests/main.cpp
tests/test_testclass.cpp
src/TestClass.cpp
)

target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Catch2/contrib/")

include(CTest)
include(Catch)
catch_discover_tests(tests)