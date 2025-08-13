#include "branching/dfs_brancher.h"
#include "solver.h"
#include "variables/variable.h"

std::optional<Decision> DFSBrancher::next(const Solver &context)
{
    const auto &variables = context.get_variables();
    for (IVariable *var : variables)
    {
        if (!var->is_fixed())
        {
            // Return the first unfixed variable with its lower bound value
            return Decision(var, var->lower_bound());
        }
    }
    // All variables are assigned
    return std::nullopt;
}