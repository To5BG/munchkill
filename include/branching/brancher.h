#pragma once

#include <optional>

class IVariable;
class AtomicConstraint;
class SolverContext;

/// @brief Represents a branching decision (variable and value to assign)
struct BranchingDecision
{
    IVariable *variable;
    int value;

    BranchingDecision(IVariable *var, int val) : variable(var), value(val) {}
};

/// @brief Interface for branching strategies that decide which variable and value to choose
class IBrancher
{
public:
    virtual ~IBrancher() = default;

    /// @brief Select the next variable and value to branch on
    /// @param context The solver context
    /// @return A branching decision or nullopt if all variables are assigned
    virtual std::optional<BranchingDecision> select_branch(const SolverContext &context) = 0;

    /// @brief Notify the brancher about a backtrack operation
    /// @param new_level The level we backtracked to
    virtual void on_backtrack(unsigned int new_level) {}
};
