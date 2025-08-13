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
    bool is_satisfied() const override;
    bool is_violated() const override;

    AtomicConstraint invert();

    IVariable *get_variable() const;
    Operator get_operator() const;
    int get_constant() const;
};