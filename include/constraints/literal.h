#pragma once

#include "constraints/constraint.h"
#include "utils/operator.h"
#include "variables/variable.h"

class Literal : public IConstraint
{
public:
    IVariable *var;
    Operator op;
    int constant;

    Literal() = default;
    Literal(IVariable *var, Operator op, int constant);

    void propagate() override;
    bool is_satisfied() const override;
    bool is_violated() const override;

    Literal invert();

    std::string to_string() const
    {
        return "[" + var->id + op2str(op) + std::to_string(constant) + "]";
    }
};