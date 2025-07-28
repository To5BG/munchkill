#include "constraints/not_equals.h"

NotEqualsConstraint::NotEqualsConstraint(IVariable *lhs, IVariable *rhs) : lhs(lhs),
                                                                           rhs(rhs)
{
    std::cout << "NotEqualsConstraint created" << std::endl;
}

void NotEqualsConstraint::propagate()
{
    std::cout << "123" << std::endl;
}
