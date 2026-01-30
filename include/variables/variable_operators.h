#pragma once

#include "constraints/literal.h"

// Forward declarations
class IVariable;

/// @brief Operator overloads for creating literals from variables
/// These are separated to avoid circular dependencies between variable.h and literal.h

inline Literal operator>=(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::GE, constant);
}

inline Literal operator<=(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::LE, constant);
}

inline Literal operator==(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::EQ, constant);
}

inline Literal operator!=(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::NE, constant);
}