#include <catch2/catch.hpp>

#include <iostream>
#include <vector>
#include "CSV.hpp"

TEST_CASE( "Unit testing class: TestClass", "[TestClass]" ) {

    auto data = CSV::readIntegerCSV("data/test.csv");
    REQUIRE( data[0][0] == 1);
    REQUIRE( data[2][1] == -1);
}