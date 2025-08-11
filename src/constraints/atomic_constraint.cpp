#include "constraints/atomic_constraint.h"

AtomicConstraint::AtomicConstraint(IVariable *var, Operator op, int constant) :
    var(var), 
    op(op), 
    constant(constant)
{
    
}

void AtomicConstraint::propagate()
{
    //TODO
}

bool AtomicConstraint::isSatisfied() const
{
    //TODO
    return false;
}

bool AtomicConstraint::isViolated() const
{
    //TODO
    return false;
}

AtomicConstraint AtomicConstraint::invert()
{
    Operator invertedOp;
    switch (op) {
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

IVariable* AtomicConstraint::getVariable() const
{
    return var;
}

Operator AtomicConstraint::getOperator() const
{
    return op;
}

int AtomicConstraint::getConstant() const
{
    return constant;
}