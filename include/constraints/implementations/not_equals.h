#pragma once

#include <iostream>
#include "../constraint.h"
#include "../../variables/variable.h"

class NotEqualsConstraint : public IConstraint
{
private:
    IVariable* lhs;
    IVariable* rhs;

public:
    NotEqualsConstraint(IVariable* lhs, IVariable* rhs);

    void propagate() override;
};