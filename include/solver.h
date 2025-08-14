#pragma once

#include <vector>
#include "constraints/constraint.h"
#include "propagation/propagator_queue.h"
#include "propagation/propagation_status.h"
#include "trail.h"

// Forward declarations
class IVariable;
class Literal;
class IBrancher;

/// @brief Overall state of the solver
enum class SolverState
{
    Ready,       // Ready to solve
    Solving,     // Currently solving
    Satisfiable, // Solution found
    Infeasible,  // No solution exists
    Timeout      // Solver timed out
};

class Solver
{
private:
    std::vector<IVariable *> variables;
    std::vector<IConstraint *> constraints;
    Trail trail;
    PropagatorQueue propagator_queue;
    IBrancher *brancher;

    // DecisionResult enqueueNextDecision();
    void enqueue_next_decision();
    void declare_new_decision_level();
    void handle_conflict();

    IVariable *select_variable_to_split();
    void propagate(Literal ac);
    void backtrack(unsigned int newLevel);

public:
    explicit Solver(IBrancher *brancher);

    SolverState solver_state = SolverState::Ready;

    bool solve();
    void add_variable(IVariable *variable);
    void add_constraint(IConstraint *constraint);

    bool are_any_constraints_violated() const;

    bool is_conflicting() const { return solver_state == SolverState::Infeasible || are_any_constraints_violated(); }
    bool has_solution() const { return solver_state == SolverState::Satisfiable; }

    const std::vector<IVariable *> &get_variables() const { return variables; }
};