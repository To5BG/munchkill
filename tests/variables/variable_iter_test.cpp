#include <catch2/catch.hpp>
#include "variables/variable_single_holes.h"
#include <vector>

TEST_CASE("DomainIterator", "[variable]")
{
    SECTION("Init full")
    {
        VariableSingleHoles var("v", 0, 3);
        REQUIRE(var.domain() == std::vector<int>{0, 1, 2, 3});
    }

    SECTION("Init single")
    {
        VariableSingleHoles var("v", 0, 0);
        REQUIRE(var.domain() == std::vector<int>{0});
    }

    SECTION("Init holes")
    {
        VariableSingleHoles var("v", 0, 3);
        var.update(Operator::NE, 1);
        var.update(Operator::NE, 3);
        REQUIRE(var.domain() == std::vector<int>{0, 2});
    }

    SECTION("Init and undo")
    {
        VariableSingleHoles var("v", 0, 3);
        var.update(Operator::NE, 1);
        var.update(Operator::NE, 3);
        var.undo(Operator::NE, 1);
        REQUIRE(var.domain() == std::vector<int>{0, 1, 2});
    }
}