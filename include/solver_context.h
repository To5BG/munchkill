#pragma once

#include <vector>
#include <stack>
#include "variables/variable.h"
#include "constraints/constraint.h"
#include "constraints/atomic_constraint.h"

class IVariable;
class AtomicConstraint;

class SolverContext
{
private:
    std::vector<IVariable *> variables;
    std::vector<IConstraint *> constraints;
    std::stack<AtomicConstraint> decisions;

    IVariable *select_variable_to_split();
    void propagate(AtomicConstraint ac);
    void backtrack(unsigned int newLevel);

public:
    bool solve();
    void add_variable(IVariable *variable);
    void add_constraint(IConstraint *constraint);
    bool are_any_constraints_violated() const;
};