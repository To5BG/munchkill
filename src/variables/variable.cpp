#include "variables/variable.h"
#include "constraints/implementations/atomic_constraint.h"
#include "utils/operator.h"

AtomicConstraint IVariable::operator>=(int const &constant)
{
    return AtomicConstraint(this, Operator::GE, constant);
}