#include "constraints/literal.h"

Literal::Literal(IVariable *var, Operator op, int constant) : var(var),
                                                              op(op),
                                                              constant(constant)
{
}

void Literal::propagate()
{
}

bool Literal::is_satisfied() const
{
    return true;
}

bool Literal::is_violated() const
{
    return false;
}

Literal Literal::invert()
{
    Operator invertedOp;
    switch (op)
    {
    case Operator::EQ:
        invertedOp = Operator::NE;
        break;
    case Operator::NE:
        invertedOp = Operator::EQ;
        break;
    case Operator::GE:
        invertedOp = Operator::LE;
        break;
    case Operator::LE:
        invertedOp = Operator::GE;
        break;
    }
    return Literal(var, invertedOp, constant);
}