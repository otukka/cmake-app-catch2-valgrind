#include <catch2/catch.hpp>

#include "ExampleClass.hpp"

TEST_CASE( "Unit testing class: ExampleClass", "[ExampleClass]" ) {
    ExampleClass  tc = ExampleClass();
    REQUIRE( tc.func() == 1);
}