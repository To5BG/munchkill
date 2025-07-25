#include "constraints/implementations/not_equals.h"

NotEqualsConstraint::NotEqualsConstraint(IVariable* lhs, IVariable* rhs) 
{
    std::cout << "NotEqualsConstraint created" << std::endl;
    this->lhs = lhs;
    this->rhs = rhs;
}

void NotEqualsConstraint::propagate() 
{
    std::cout << "123" << std::endl;
}

