#include <catch2/catch.hpp>
#include "variables/variable_single_holes.h"
#include "../test_utils.h"
#include <ranges>

const int INIT_LB = 0;
const int INIT_UB = 3;

TEST_CASE("VariableSingleHoles", "[variable]")
{
    VariableSingleHoles var("v", INIT_LB, INIT_UB);
    SECTION("Init")
    {
        assert_var_state(var, INIT_LB, INIT_UB, std::vector<int>{0, 1, 2, 3}, std::nullopt);
    }
}

TEST_CASE("VariableSingleHoles - Removal", "[variable]")
{
    VariableSingleHoles var("v", INIT_LB, INIT_UB);
    // Removing individual values
    for (int i = INIT_LB; i <= INIT_UB; i++)
    {
        DYNAMIC_SECTION(fmt::format("Removing a hole at {}", i))
        {
            // Update
            var.update(Operator::NE, i);
            REQUIRE(var.domain().size() == (INIT_UB - INIT_LB));
            // Undo
            var.undo(DomainChange{INIT_LB, INIT_UB, i});
            assert_var_state(var, INIT_LB, INIT_UB, std::vector<int>{0, 1, 2, 3}, std::nullopt);
        }
    }

    SECTION("All but one holes")
    {
        // Generate a permutation of the hole removal order
        auto removal_order = GENERATE_REF(
            std::vector<int>{1, 2, 3},
            std::vector<int>{1, 3, 2},
            std::vector<int>{2, 1, 3},
            std::vector<int>{2, 3, 1},
            std::vector<int>{3, 1, 2},
            std::vector<int>{3, 2, 1});
        CAPTURE(removal_order);
        // Update
        for (int i : removal_order)
            var.update(Operator::NE, i);
        assert_var_state(var, 0, 0, std::vector<int>{0}, 0);
        // Undo one - check boundaries and other two holes
        int ub = removal_order.back();
        var.undo(DomainChange{0, ub, removal_order.back()});
        REQUIRE_FALSE((var.is_valid(removal_order[0]) || var.is_valid(removal_order[1])));
        assert_var_state(var, 0, removal_order.back(), std::vector<int>{0, removal_order.back()}, std::nullopt);
        // Undo the rest
        var.undo(DomainChange{0, std::max(removal_order[1], ub), removal_order[1]});
        var.undo(DomainChange{0, INIT_UB, removal_order[0]});
        assert_var_state(var, 0, INIT_UB, std::vector<int>{0, 1, 2, 3}, std::nullopt);
    }
}

TEST_CASE("VariableSingleHoles - Bounds", "[variable]")
{
    VariableSingleHoles var("v", INIT_LB, INIT_UB);
    // Update lower bound of continuous variable
    for (int i = INIT_LB; i <= INIT_UB; i++)
    {
        DYNAMIC_SECTION(fmt::format("Setting lower bound to {}", i))
        {
            // Update
            var.update(Operator::GE, i);
            auto r = std::views::iota(i, INIT_UB + 1);
            assert_var_state(var, i, INIT_UB, std::vector<int>(r.begin(), r.end()),
                             i == INIT_UB ? std::optional<int>{INIT_UB} : std::nullopt);
            // Undo
            var.undo(DomainChange{INIT_LB, var.upper_bound(), std::nullopt});
            assert_var_state(var, INIT_LB, INIT_UB, std::vector<int>{0, 1, 2, 3}, std::nullopt);
        }
    }
    // Update upper bound of continuous variable
    for (int i = INIT_LB; i <= INIT_UB; i++)
    {
        DYNAMIC_SECTION(fmt::format("Setting upper bound to {}", i))
        {
            // Update
            var.update(Operator::LE, i);
            auto r = std::views::iota(INIT_LB, i + 1);
            assert_var_state(var, INIT_LB, i, std::vector<int>(r.begin(), r.end()),
                             i == INIT_LB ? std::optional<int>{INIT_LB} : std::nullopt);
            // Undo
            var.undo(DomainChange{var.lower_bound(), INIT_UB, std::nullopt});
            assert_var_state(var, INIT_LB, INIT_UB, std::vector<int>{0, 1, 2, 3}, std::nullopt);
        }
    }

    SECTION("Updating bounds on var with holes")
    {
        // Update lower bound at a hole
        var.update(Operator::NE, 1);
        assert_var_state(var, 0, 3, std::vector<int>{0, 2, 3}, std::nullopt);
        var.update(Operator::GE, 1);
        assert_var_state(var, 2, 3, std::vector<int>{2, 3}, std::nullopt);
        // Add another hole
        var.update(Operator::NE, 2);
        assert_var_state(var, 3, 3, std::vector<int>{3}, 3);
        // Undo in reverse
        var.undo(DomainChange{2, 3, 2});
        assert_var_state(var, 2, 3, std::vector<int>{2, 3}, std::nullopt);
        var.undo(DomainChange{0, var.upper_bound(), std::nullopt});
        assert_var_state(var, 0, 3, std::vector<int>{0, 2, 3}, std::nullopt);
        var.undo(DomainChange{0, var.upper_bound(), 1});
        assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
    }
}