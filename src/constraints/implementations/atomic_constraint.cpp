#include "constraints/implementations/atomic_constraint.h"

AtomicConstraint::AtomicConstraint(IVariable *var, Operator op, int constant) :
    var(var), 
    op(op), 
    constant(constant)
{
    
}

void AtomicConstraint::propagate()
{
    
}
