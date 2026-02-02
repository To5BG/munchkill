#include <catch2/catch.hpp>
#include <random>
#include "variables/variable_single_holes.h"
#include "test_utils.h"
#include "trail_assignment.h"
#include "variables/variable_operators.h"

TEST_CASE("Trail", "[component]")
{
    SECTION("Verify reversibility")
    {
        Trail<AssignmentTrailEntry, Literal> trail;
        VariableSingleHoles var("v", 0, 10);
        trail.next_decision_level();
        Literal l = Literal(
            &var,
            GENERATE(Operator::NE, Operator::GE, Operator::LE, Operator::EQ),
            GENERATE(take(10, random(0, 10))));
        trail.push(l);
        INFO(l.to_string());
        trail.backtrack(0);
        assert_var_state(var, 0, 10, std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, std::nullopt);
    }
}