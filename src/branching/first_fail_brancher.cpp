#include "branching/first_fail_brancher.h"
#include "solver.h"
#include "variables/variable.h"
#include <climits>

std::optional<Decision> FirstFailBrancher::next(const std::vector<IVariable *> &vars)
{
    IVariable *best_var = nullptr;
    int smallest_domain = INT_MAX;

    // Find the variable with the smallest domain that is not yet fixed
    for (IVariable *var : vars)
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
    return Decision(best_var, best_var->lower_bound());
}