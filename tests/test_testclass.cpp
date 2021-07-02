#include <catch2/catch.hpp>

#include "TestClass.hpp"

TEST_CASE( "Unit testing class: TestClass", "[TestClass]" ) {
    TestClass  tc = TestClass();
    REQUIRE( tc.func() == 1);
}