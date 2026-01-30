#include "solver.h"
#include "variables/variable.h"
#include "constraints/literal.h"
#include "branching/brancher.h"
#include "variables/variable_operators.h"

Solver::Solver(IBrancher *brancher) : brancher(brancher)
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif
}

bool Solver::solve()
{
    // Initialize solver state
    solver_state = SolverState::Solving;
    spdlog::info("Solver starting...");
    // Main loop
    while (true)
    {
        spdlog::debug("Trail state: {}", trail.to_string());
        // TODO: add propagation
        if (!is_conflicting())
        {
            std::optional<Decision> branch_decision = brancher->next(this->get_variables());
            // If no decision -> all variables assigned
            if (!branch_decision.has_value())
            {
                spdlog::info("Solution found.");
                solver_state = SolverState::Satisfiable;
                return true;
            }
            else
            {
                spdlog::debug("Decision at level {}: {} = {}",
                              trail.get_current_level(), branch_decision->variable->id, branch_decision->value);
            }
            // Make decision
            trail.next_decision_level();
            // Check for conflict upon decision
            if (!trail.push(*branch_decision->variable == branch_decision->value))
                solver_state = SolverState::Infeasible;
        }
        else
        {
            int curr_level = trail.get_current_level();
            // Infeasible if at root
            if (curr_level == 0)
            {
                spdlog::info("Problem is infeasible.");
                solver_state = SolverState::Infeasible;
                return false;
            }
            Literal last_decision = trail.backtrack(curr_level - 1);
            spdlog::debug("Backtracking to level {}: Inverting decision {} = {}",
                          trail.get_current_level(), last_decision.var->id, last_decision.constant);
            // Invert last decision as a propagation
            trail.push(*last_decision.var != last_decision.constant);
            solver_state = SolverState::Solving;
        }
    }
}

void Solver::add_variable(IVariable *variable)
{
    variables.push_back(variable);
}

void Solver::add_constraint(IConstraint *constraint)
{
    constraints.push_back(constraint);
}