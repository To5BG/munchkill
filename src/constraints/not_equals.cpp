#include "constraints/not_equals.h"

NotEqualsConstraint::NotEqualsConstraint(IVariable* lhs, IVariable* rhs) :
    lhs(lhs),
    rhs(rhs)
{
    std::cout << "NotEqualsConstraint created" << std::endl;
}

void NotEqualsConstraint::propagate() 
{
    // TODO
    std::cout << "123" << std::endl;
}

bool NotEqualsConstraint::isSatisfied() const
{
    // TODO
    return false;
}

bool NotEqualsConstraint::isViolated() const
{
    // TODO
    return false;
}
