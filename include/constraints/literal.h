#pragma once

#include "constraints/constraint.h"
#include "utils/operator.h"

// Forward declarations
class IVariable;

class Literal : public IConstraint
{
private:
    IVariable *var;
    Operator op;
    int constant;

public:
    Literal() = default;
    Literal(IVariable *var, Operator op, int constant);

    void propagate() override;
    bool is_satisfied() const override;
    bool is_violated() const override;

    Literal invert();

    IVariable *get_variable() const;
    Operator get_operator() const;
    int get_constant() const;
};