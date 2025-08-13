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
}

bool Literal::is_violated() const
{
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

IVariable *Literal::get_variable() const
{
    return var;
}

Operator Literal::get_operator() const
{
    return op;
}

int Literal::get_constant() const
{
    return constant;
}
