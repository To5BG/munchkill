#pragma once

#include <optional>
#include <stack>
#include <vector>
#include "constraints/atomic_constraint.h"
#include "solver_context.h"
#include "variables/domain_event.h"

class AtomicConstraint;
class SolverContext;

/// @brief Interface for integer variables.
class IVariable
{

public:
    /// @brief Remove a value from the variable's domain.
    /// @param value Value to remove.
    virtual void remove(SolverContext &context, int value) = 0;

    /// @brief Sets the lower bound of the variable.
    /// @param value New lower bound value.
    virtual void setLowerBound(SolverContext &context, int value) = 0;

    /// @brief Sets the upper bound of the variable.
    /// @param value New upper bound value.
    virtual void setUpperBound(SolverContext &context, int value) = 0;

    // TODO Documentation
    virtual void backtrack(unsigned int newLevel) = 0;

    /// @brief Undo a domain modification
    /// @param event The type of domain event to undo
    /// @param value The value involved in the undo operation
    virtual void undo(DomainEvent event, int value) = 0;

    /// @brief Get the lower bound of the variable.
    virtual int lowerBound() const = 0;

    /// @brief Get the upper bound of the variable.
    virtual int upperBound() const = 0;

    virtual std::optional<int> assignedValue() const = 0;

    virtual bool isFixed() const = 0;

    AtomicConstraint operator>=(int const &constant);
    AtomicConstraint operator<=(int const &constant);
    AtomicConstraint operator==(int const &constant);
    AtomicConstraint operator!=(int const &constant);
};