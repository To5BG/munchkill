#include <catch2/catch.hpp>
#include <random>
#include "variables/variable_single_holes.h"
#include "test_utils.h"
#include "trail_assignment.h"
#include "variables/variable_operators.h"

TEST_CASE("Trail", "[component]")
{
    Trail<AssignmentTrailEntry, Literal> trail;
    VariableSingleHoles var("v", 0, 10);
    // Generate separately as Catch2 does not support dynamic nested generators
    auto op1 = GENERATE(Operator::NE, Operator::GE, Operator::LE, Operator::EQ);
    auto v1 = GENERATE(range(1, 10));
    Literal l1(&var, op1, v1);
    auto op2 = GENERATE(Operator::NE, Operator::GE, Operator::LE, Operator::EQ);
    auto v2 = GENERATE(range(1, 10));
    Literal l2(&var, op2, v2);

    CAPTURE(l1.to_string(), l2.to_string(), var.is_fixed(), var.lower_bound(), var.upper_bound());
    trail.next_decision_level();
    trail.push(l1);
    trail.next_decision_level();
    trail.push(l2);

    trail.backtrack(0);
    assert_var_state(var, 0, 10, std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, std::nullopt);
}