#include "branching/dfs_brancher.h"
#include "solver_context.h"
#include "variables/variable.h"

std::optional<BranchingDecision> DFSBrancher::selectBranch(const SolverContext &context)
{
    const auto &variables = context.getVariables();
    for (IVariable *var : variables)
    {
        if (!var->isFixed())
        {
            // Return the first unfixed variable with its lower bound value
            return BranchingDecision(var, var->lowerBound());
        }
    }
    // All variables are assigned
    return std::nullopt;
}
