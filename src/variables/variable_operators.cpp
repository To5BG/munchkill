#include "variables/variable_operators.h"
#include "utils/operator.h"

Literal operator>=(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::GE, constant);
}

Literal operator<=(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::LE, constant);
}

Literal operator==(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::EQ, constant);
}

Literal operator!=(const IVariable &var, int constant)
{
    return Literal(const_cast<IVariable *>(&var), Operator::NE, constant);
}