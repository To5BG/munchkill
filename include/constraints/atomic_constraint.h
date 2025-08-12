#pragma once
#include "constraints/constraint.h"
#include "variables/variable.h"
#include "utils/operator.h"

class IConstraint;
class IVariable;

class AtomicConstraint : public IConstraint
{
private:
    IVariable *var;
    Operator op;
    int constant;

public:
    AtomicConstraint() = default;
    AtomicConstraint(IVariable *var, Operator op, int constant);

    void propagate() override;
    bool isSatisfied() const override;
    bool isViolated() const override;

    AtomicConstraint invert();

    IVariable *getVariable() const;
    Operator getOperator() const;
    int getConstant() const;
};