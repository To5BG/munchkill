#include "solver_context.h"
#include <stdexcept>

SolverContext::SolverContext(IBrancher *brancher) : brancher(brancher)
{
    if (brancher == nullptr)
    {
        throw std::invalid_argument("Brancher cannot be null");
    }
}

bool SolverContext::solve()
{
    // Initialize solver state
    solver_state = SolverState::Solving;
    // Main loop
    while (true)
    {
        // TODO: add propagation
        if (!is_conflicting())
        {
            auto branch_decision = brancher->next(*this);
            if (!branch_decision.has_value())
            {
                // All variables are assigned - we have a solution
                return true;
            }
            // Make decision
            trail.next_decision_level();
            trail.push(branch_decision->variable, DomainEvent::Assign, branch_decision->value);
        }
        else
        {
            // Infeasible if at root
            if (trail.get_current_level() == 0)
            {
                solver_state = SolverState::Infeasible;
                return false;
            }
            TrailEntry last_decision = trail.backtrack(trail.get_current_level() - 1);
            // Invert last decision as a propagation
            trail.push(last_decision.variable, DomainEvent::Removal, last_decision.value);
            solver_state = SolverState::Solving;
        }
    }
}

bool SolverContext::are_any_constraints_violated() const
{
    for (auto constraint : constraints)
    {
        if (constraint->is_violated())
        {
            return true;
        }
    }
    return false;
}

void SolverContext::add_variable(IVariable *variable)
{
    variables.push_back(variable);
}

void SolverContext::add_constraint(IConstraint *constraint)
{
    constraints.push_back(constraint);
}