#pragma once

/// @brief Interface for integer variables.
class IVariable 
{

public:
    /// @brief Remove a value from the variable's domain.
    /// @param value Value to remove.
    virtual void remove(int value) = 0;

    /// @brief Sets the lower bound of the variable.
    /// @param value New lower bound value.
    virtual void setLowerBound(int value) = 0;

    /// @brief Sets the upper bound of the variable.
    /// @param value New upper bound value.
    virtual void setUpperBound(int value) = 0;

    /// @brief Get the lower bound of the variable.
    virtual int lowerBound() = 0;

    /// @brief Get the upper bound of the variable.
    virtual int upperBound() = 0;
};