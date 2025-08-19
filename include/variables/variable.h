#pragma once

#include <optional>
#include "utils/domain_event.h"
#include "utils/asserts.h"

/// @brief Interface for integer variables.
class IVariable
{

private:
    /// @brief Remove a value from the variable's domain.
    virtual bool remove(int value) = 0;

    /// @brief Sets the lower bound of the variable.
    virtual bool set_lower_bound(int value) = 0;

    /// @brief Sets the upper bound of the variable.
    virtual bool set_upper_bound(int value) = 0;

    /// @brief Assign a value to the variable.
    virtual bool assign(int value) = 0;

public:
    /// @brief Update the variable based on the domain event.
    inline bool update(DomainEvent event, int value)
    {
        if (!assert_warn(!is_fixed(), "Attempting to modify a fixed variable"))
            return false;
        switch (event)
        {
        case DomainEvent::Assign:
            return assign(value);
        case DomainEvent::Removal:
            return remove(value);
        case DomainEvent::LowerBound:
            return set_lower_bound(value);
        case DomainEvent::UpperBound:
            return set_upper_bound(value);
        }
        return false;
    }

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