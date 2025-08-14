#pragma once

#include "variables/variable.h"
#include "constraints/literal.h"

/// @brief Operator overloads for creating literals from variables
/// These are separated to avoid circular dependencies between variable.h and literal.h

Literal operator>=(const IVariable &var, int constant);
Literal operator<=(const IVariable &var, int constant);
Literal operator==(const IVariable &var, int constant);
Literal operator!=(const IVariable &var, int constant);
