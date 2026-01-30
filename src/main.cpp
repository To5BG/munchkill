#include <fmt/core.h>
#include "constraints/not_equals.h"
#include "variables/variable_single_holes.h"
#include "solver.h"
#include "branching/dfs_brancher.h"

int main()
{
    VariableSingleHoles v1("v1", 1, 3), v2("v2", 1, 2), v3("v3", 1, 2);
    NotEqualsConstraint c1(&v1, &v2), c2(&v2, &v3), c3(&v1, &v3);

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
        for (auto &v : {v1, v2, v3})
            fmt::print("{}={}\n", v.id, v.assigned_value().value());
    }
    return 0;
}
