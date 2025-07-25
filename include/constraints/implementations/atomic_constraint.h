#pragma once
#include "constraints/constraint.h"
#include "utils/operator.h"
#include "variables/variable.h"

class AtomicConstraint : public IConstraint 
{
private:
    const IVariable* var;
    const Operator op;
    const int constant;

public:
    AtomicConstraint(IVariable* var, Operator op, int constant);

    void propagate() override;
};