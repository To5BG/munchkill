#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "constraints/not_equals.h"
#include "variables/variable_single_holes.h"
#include "solver.h"
#include "branching/dfs_brancher.h"

int main()
{
    // Print using fmt
    fmt::print("Hello, {}!\n", "world");
    // Print using spdlog
    spdlog::info("This is an info message from spdlog.");
    spdlog::warn("This is a warning.");
    spdlog::error("This is an error message.");

    VariableSingleHoles v1(1, 3), v2(1, 2), v3(1, 2);
    NotEqualsConstraint c1(&v1, &v2), c2(&v2, &v3), c3(&v1, &v3);

    // Create a DFS brancher
    DFSBrancher brancher;
    Solver context(&brancher);

    context.add_variable(&v1);
    context.add_variable(&v2);
    context.add_variable(&v3);
    context.add_constraint(&c1);
    context.add_constraint(&c2);
    context.add_constraint(&c3);

    bool result = context.solve();
    if (result)
    {
        std::cout << "Solution found!" << std::endl;
        std::cout << "v1=" << v1.assigned_value().value() << std::endl;
        std::cout << "v2=" << v2.assigned_value().value() << std::endl;
        std::cout << "v3=" << v3.assigned_value().value() << std::endl;
    }
    else
    {
        std::cout << "Impossible." << std::endl;
    }

    return 0;
}
