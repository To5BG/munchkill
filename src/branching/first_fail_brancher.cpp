#include "branching/first_fail_brancher.h"
#include "solver.h"
#include "variables/variable.h"
#include <climits>

std::optional<BranchingDecision> FirstFailBrancher::next(const Solver &context)
{
    IVariable *best_var = nullptr;
    int smallest_domain = INT_MAX;

    // Find the variable with the smallest domain that is not yet fixed
    const auto &variables = context.get_variables();
    for (IVariable *var : variables)
    {
        if (!var->is_fixed())
        {
            int domain_size = var->upper_bound() - var->lower_bound() + 1;
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
    return BranchingDecision(best_var, best_var->lower_bound());
}