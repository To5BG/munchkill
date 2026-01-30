#pragma once
#include <catch2/catch.hpp>
#include <vector>
#include <optional>
#include <string>

// Helper to run all checks in a single REQUIRE to not clutter log
template <typename T>
inline void assert_var_state(T &var, int lb, int ub, std::vector<int> dom, std::optional<int> assigned)
{
    INFO(fmt::format("lower_bound: expected {}, got {}", lb, var.lower_bound()));
    INFO(fmt::format("upper_bound: expected {}, got {}", ub, var.upper_bound()));
    INFO(fmt::format("assigned_value: expected {}, got {}",
                     assigned.has_value() ? std::to_string(assigned.value()) : "nullopt",
                     var.assigned_value().has_value() ? std::to_string(var.assigned_value().value()) : "nullopt"));
    INFO(fmt::format("domain: expected {{{}}}, got {{{}}}", fmt::join(dom, ", "), fmt::join(var.domain(), ", ")));
    REQUIRE((var.lower_bound() == lb &&
             var.upper_bound() == ub &&
             var.assigned_value() == assigned &&
             var.domain() == dom));
}
