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
    /// @brief Update the variable based on the domain event.
    /// @param event The domain event that occurred.
    /// @param value The value associated with the event.
    void update(DomainEvent event, int value)
    {
        switch (event)
        {
        case DomainEvent::Assign:
            assign(value);
            break;
        case DomainEvent::Removal:
            remove(value);
            break;
        case DomainEvent::LowerBound:
            set_lower_bound(value);
            break;
        case DomainEvent::UpperBound:
            set_upper_bound(value);
            break;
        }
    }

    /// @brief Remove a value from the variable's domain.
    /// @param value Value to remove.
    virtual void remove(int value) = 0;

    /// @brief Sets the lower bound of the variable.
    /// @param value New lower bound value.
    virtual void set_lower_bound(int value) = 0;

    /// @brief Sets the upper bound of the variable.
    /// @param value New upper bound value.
    virtual void set_upper_bound(int value) = 0;

    /// @brief Assign a value to the variable.
    /// @param value Value to assign.
    virtual void assign(int value) = 0;

    /// @brief Undo a domain modification
    /// @param event The type of domain event to undo
    /// @param value The value involved in the undo operation
    virtual void undo(DomainEvent event, int value) = 0;

    /// @brief Get the lower bound of the variable.
    virtual int lower_bound() const = 0;

    /// @brief Get the upper bound of the variable.
    virtual int upper_bound() const = 0;

    virtual std::optional<int> assigned_value() const = 0;

    virtual bool is_fixed() const = 0;

    AtomicConstraint operator>=(int const &constant);
    AtomicConstraint operator<=(int const &constant);
    AtomicConstraint operator==(int const &constant);
    AtomicConstraint operator!=(int const &constant);
};