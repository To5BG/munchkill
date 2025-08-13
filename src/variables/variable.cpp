#include "variables/variable.h"
#include "constraints/literal.h"
#include "utils/operator.h"

Literal IVariable::operator>=(int const &constant)
{
    return Literal(this, Operator::GE, constant);
}

Literal IVariable::operator<=(int const &constant)
{
    return Literal(this, Operator::LE, constant);
}

Literal IVariable::operator==(int const &constant)
{
    return Literal(this, Operator::EQ, constant);
}

Literal IVariable::operator!=(int const &constant)
{
    return Literal(this, Operator::NE, constant);
}