#include <catch2/catch.hpp>
#include "variables/variable_single_holes.h"
#include "../test_utils.h"
#include <ranges>

TEST_CASE("VariableSingleHoles", "[variable]")
{
    VariableSingleHoles var("v", 0, 3);
    SECTION("Init")
    {
        assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
    }
}

TEST_CASE("VariableSingleHoles - Removal", "[variable]")
{
    VariableSingleHoles var("v", 0, 3);
    // Removing individual values
    for (int i = 0; i <= 3; i++)
    {
        DYNAMIC_SECTION(fmt::format("Removing a hole at {}", i))
        {
            // Update
            var.update(DomainEvent::Removal, i);
            REQUIRE(var.domain().size() == 3);
            // Undo
            var.undo(DomainEvent::Removal, i);
            assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
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
            var.update(DomainEvent::Removal, i);
        assert_var_state(var, 0, 0, std::vector<int>{0}, 0);
        // Undo one - check boundaries and other two holes
        var.undo(DomainEvent::Removal, removal_order.back());
        REQUIRE_FALSE((var.is_valid(removal_order[0]) || var.is_valid(removal_order[1])));
        assert_var_state(var, 0, removal_order.back(), std::vector<int>{0, removal_order.back()}, std::nullopt);
        // Undo the rest
        var.undo(DomainEvent::Removal, removal_order[1]);
        var.undo(DomainEvent::Removal, removal_order[0]);
        assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
    }
}

TEST_CASE("VariableSingleHoles - Bounds", "[variable]")
{
    VariableSingleHoles var("v", 0, 3);
    // Update lower bound of continuous variable
    for (int i = 0; i <= 3; i++)
    {
        DYNAMIC_SECTION(fmt::format("Setting lower bound to {}", i))
        {
            // Update
            var.update(DomainEvent::LowerBound, i);
            auto r = std::views::iota(i, 4);
            assert_var_state(var, i, 3, std::vector<int>(r.begin(), r.end()),
                             i == 3 ? std::optional<int>{3} : std::nullopt);
            // Undo
            var.undo(DomainEvent::LowerBound, 0);
            assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
        }
    }
    // Update upper bound of continuous variable
    for (int i = 0; i <= 3; i++)
    {
        DYNAMIC_SECTION(fmt::format("Setting upper bound to {}", i))
        {
            // Update
            var.update(DomainEvent::UpperBound, i);
            auto r = std::views::iota(0, i + 1);
            assert_var_state(var, 0, i, std::vector<int>(r.begin(), r.end()),
                             i == 0 ? std::optional<int>{0} : std::nullopt);
            // Undo
            var.undo(DomainEvent::UpperBound, 3);
            assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
        }
    }

    SECTION("Updating bounds on var with holes")
    {
        // Update lower bound at a hole
        var.update(DomainEvent::Removal, 1);
        assert_var_state(var, 0, 3, std::vector<int>{0, 2, 3}, std::nullopt);
        var.update(DomainEvent::LowerBound, 1);
        assert_var_state(var, 2, 3, std::vector<int>{2, 3}, std::nullopt);
        // Add another hole
        var.update(DomainEvent::Removal, 2);
        assert_var_state(var, 3, 3, std::vector<int>{3}, 3);
        // Undo in reverse
        var.undo(DomainEvent::Removal, 2);
        assert_var_state(var, 2, 3, std::vector<int>{2, 3}, std::nullopt);
        var.undo(DomainEvent::LowerBound, 0);
        assert_var_state(var, 0, 3, std::vector<int>{0, 2, 3}, std::nullopt);
        var.undo(DomainEvent::Removal, 1);
        assert_var_state(var, 0, 3, std::vector<int>{0, 1, 2, 3}, std::nullopt);
    }
}