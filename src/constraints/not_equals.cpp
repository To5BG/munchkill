#include "constraints/not_equals.h"

NotEqualsConstraint::NotEqualsConstraint(IVariable *lhs, IVariable *rhs) : lhs(lhs),
                                                                           rhs(rhs)
{
}

void NotEqualsConstraint::propagate()
{
    // TODO
}

bool NotEqualsConstraint::isSatisfied() const
{
    auto lhsValue = lhs->assignedValue();
    auto rhsValue = rhs->assignedValue();
    return lhsValue.has_value() && rhsValue.has_value() && lhsValue.value() != rhsValue.value();
}

bool NotEqualsConstraint::isViolated() const
{
    auto lhsValue = lhs->assignedValue();
    auto rhsValue = rhs->assignedValue();
    return lhsValue.has_value() && rhsValue.has_value() && lhsValue.value() == rhsValue.value();
}
