#include "branching/dfs_brancher.h"
#include "variables/variable.h"

std::optional<Decision> DFSBrancher::next(const std::vector<IVariable *> &vars)
{
    for (IVariable *var : vars)
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