#pragma once

#include <string>
#include <array>

/// @brief Enum for the operators used in atomic constraints of the form [x @ c],
/// where x is a variable, @ is the operator and c is a constant.
enum Operator
{
    /// @brief Equals
    EQ,
    /// @brief Not Equals
    NE,
    /// @brief Greater or Equal than
    GE,
    /// @brief Lesser or Equal than
    LE,
};

constexpr std::array<const char *, 4> OperatorNames{
    " = ", " != ", " <= ", " >= "};

constexpr std::string op2str(Operator op)
{
    return OperatorNames[static_cast<size_t>(op)];
}