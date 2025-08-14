#pragma once

#include "constraints/constraint.h"

// Forward declarations
class IVariable;

class NotEqualsConstraint : public IConstraint
{
private:
    const IVariable *lhs;
    const IVariable *rhs;

public:
    NotEqualsConstraint(IVariable *lhs, IVariable *rhs);

    void propagate() override;
    bool is_satisfied() const override;
    bool is_violated() const override;
};