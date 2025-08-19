#include <catch2/catch.hpp>
#include "variables/variable_single_holes.h"

TEST_CASE("VariableSingleHoles", "[variable]")
{
    VariableSingleHoles var(0, 10);

    SECTION("Init")
    {
        REQUIRE(var.lower_bound() == 0);
        REQUIRE(var.upper_bound() == 10);
        REQUIRE_FALSE(var.is_fixed());
    }
}