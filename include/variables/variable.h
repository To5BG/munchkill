#pragma once

#include <optional>
#include "utils/operator.h"
#include "utils/asserts.h"
#include "utils/update_result.h"

/// @brief Interface for integer variables.
class IVariable
{

private:
    /// @brief Remove a value from the variable's domain.
    virtual UpdateResult remove(int value) = 0;

    /// @brief Sets the lower bound of the variable.
    virtual UpdateResult set_lower_bound(int value) = 0;

    /// @brief Sets the upper bound of the variable.
    virtual UpdateResult set_upper_bound(int value) = 0;

    /// @brief Assign a value to the variable.
    virtual UpdateResult assign(int value) = 0;

public:
    /// @brief Identifier/name for the variable.
    std::string id;

    /// @brief Update the variable based on the domain event.
    inline UpdateResult update(Operator event, int value)
    {
        switch (event)
        {
        case Operator::EQ:
            return assign(value);
        case Operator::NE:
            return remove(value);
        case Operator::GE:
            return set_lower_bound(value);
        case Operator::LE:
            return set_upper_bound(value);
        }
        return update_result::unchanged();
    }

    /// @brief Undo a domain modification
    virtual void undo(Operator event, int value) = 0;

    /// @brief Get the lower bound of the variable.
    virtual int lower_bound() const = 0;

    /// @brief Get the upper bound of the variable.
    virtual int upper_bound() const = 0;

    /// @brief Get the assigned value of the variable, if any.
    virtual std::optional<int> assigned_value() const = 0;

    /// @brief Check if the variable is fixed, i.e. a single value.
    virtual bool is_fixed() const = 0;

    /// @brief Check if a value is in the variable's domain.
    virtual bool is_valid(int value) const = 0;
};