#pragma once

#include <optional>
#include "utils/domain_event.h"
#include "utils/asserts.h"

/// @brief Interface for integer variables.
class IVariable
{

public:
    /// @brief Update the variable based on the domain event.
    inline void update(DomainEvent event, int value)
    {
        assert_warn(!is_fixed(), "Attempting to modify a fixed variable");
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
    virtual void remove(int value) = 0;

    /// @brief Sets the lower bound of the variable.
    virtual void set_lower_bound(int value) = 0;

    /// @brief Sets the upper bound of the variable.
    virtual void set_upper_bound(int value) = 0;

    /// @brief Assign a value to the variable.
    virtual void assign(int value) = 0;

    /// @brief Undo a domain modification
    virtual void undo(DomainEvent event, int value) = 0;

    /// @brief Get the lower bound of the variable.
    virtual int lower_bound() const = 0;

    /// @brief Get the upper bound of the variable.
    virtual int upper_bound() const = 0;

    /// @brief Get the assigned value of the variable, if any.
    virtual std::optional<int> assigned_value() const = 0;

    /// @brief Check if the variable is fixed, i.e. a single value.
    virtual bool is_fixed() const = 0;
};