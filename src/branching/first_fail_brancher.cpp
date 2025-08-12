#include "branching/first_fail_brancher.h"
#include "solver_context.h"
#include "variables/variable.h"
#include <climits>

std::optional<BranchingDecision> FirstFailBrancher::selectBranch(const SolverContext &context)
{
    IVariable *best_var = nullptr;
    int smallest_domain = INT_MAX;

    // Find the variable with the smallest domain that is not yet fixed
    const auto &variables = context.getVariables();
    for (IVariable *var : variables)
    {
        if (!var->isFixed())
        {
            int domain_size = var->upperBound() - var->lowerBound() + 1;
            if (domain_size < smallest_domain)
            {
                smallest_domain = domain_size;
                best_var = var;
            }
        }
    }
    if (best_var == nullptr)
    {
        return std::nullopt; // All variables are assigned
    }
    // Choose the lower bound value (simple strategy)
    return BranchingDecision(best_var, best_var->lowerBound());
}
