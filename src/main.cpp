#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "constraints/not_equals.h"
#include "variables/variable_single_holes.h"
#include "solver_context.h"

int main()
{
    // Print using fmt
    fmt::print("Hello, {}!\n", "world");
    // Print using spdlog
    spdlog::info("This is an info message from spdlog.");
    spdlog::warn("This is a warning.");
    spdlog::error("This is an error message.");
    // New C++23 feature (optional): deducing this
    auto greet = [](std::string_view name)
    {
        return fmt::format("Hi, {}! Welcome to C++23 🎉", name);
    };

    fmt::print("{}\n", greet("Munchkill"));

    VariableSingleHoles v1(1, 3), v2(1, 2), v3(1, 2);
    NotEqualsConstraint c1(&v1, &v2), c2(&v2, &v3), c3(&v1, &v3);
    SolverContext context;
    context.addVariable(&v1);
    context.addVariable(&v2);
    context.addVariable(&v3);
    context.addConstraint(&c1);
    context.addConstraint(&c2);
    context.addConstraint(&c3);

    bool result = context.solve();
    if (result)
    {
        std::cout << "Solution found!" << std::endl;
        std::cout << "v1=" << v1.assignedValue().value() << std::endl;
        std::cout << "v2=" << v2.assignedValue().value() << std::endl;
        std::cout << "v3=" << v3.assignedValue().value() << std::endl;
    }
    else
    {
        std::cout << "Impossible." << std::endl;
    }

    return 0;
}
