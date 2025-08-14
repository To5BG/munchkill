#include "constraints/not_equals.h"
#include "variables/variable.h"

NotEqualsConstraint::NotEqualsConstraint(IVariable *lhs, IVariable *rhs) : lhs(lhs),
                                                                           rhs(rhs)
{
}

void NotEqualsConstraint::propagate()
{
    // TODO
}

bool NotEqualsConstraint::is_satisfied() const
{
    auto lhsValue = lhs->assigned_value();
    auto rhsValue = rhs->assigned_value();
    return lhsValue.has_value() && rhsValue.has_value() && lhsValue.value() != rhsValue.value();
}

bool NotEqualsConstraint::is_violated() const
{
    auto lhsValue = lhs->assigned_value();
    auto rhsValue = rhs->assigned_value();
    return lhsValue.has_value() && rhsValue.has_value() && lhsValue.value() == rhsValue.value();
}
