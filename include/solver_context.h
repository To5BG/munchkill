#pragma once

#include <vector>
#include <stack>
#include "variables/variable.h"
#include "constraints/constraint.h"
#include "constraints/implementations/atomic_constraint.h"

class IVariable;
class AtomicConstraint;

class SolverContext 
{
private:
    std::vector<IVariable> variables;
    std::vector<IConstraint> constraints;
    std::stack<AtomicConstraint> decisions;

    IVariable* selectVariableToSplit();
    bool areAnyConstraintsViolated() const;
    void propagate(AtomicConstraint ac);
    void backtrack(unsigned int newLevel);

public: 
    bool solve();
    unsigned int getDecisionLevel() const;
}; 