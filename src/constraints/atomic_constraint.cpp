#include "constraints/atomic_constraint.h"

AtomicConstraint::AtomicConstraint(IVariable *var, Operator op, int constant) : var(var),
                                                                                op(op),
                                                                                constant(constant)
{
}

void AtomicConstraint::propagate()
{
    // TODO
}

bool AtomicConstraint::is_satisfied() const
{
    // TODO
    return false;
}

bool AtomicConstraint::is_violated() const
{
    // TODO
    return false;
}

AtomicConstraint AtomicConstraint::invert()
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

    return AtomicConstraint(var, invertedOp, constant);
}

IVariable *AtomicConstraint::get_variable() const
{
    return var;
}

Operator AtomicConstraint::get_operator() const
{
    return op;
}

int AtomicConstraint::get_constant() const
{
    return constant;
}
