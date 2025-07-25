#pragma once

#include <iostream>
#include "constraints/constraint.h"
#include "variables/variable.h"

class NotEqualsConstraint : public IConstraint
{
private:
    const IVariable* lhs;
    const IVariable* rhs;

public:
    NotEqualsConstraint(IVariable* lhs, IVariable* rhs);

    void propagate() override;
};