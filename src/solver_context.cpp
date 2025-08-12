#include "solver_context.h"
#include <stdexcept>

bool SolverContext::solve()
{
    while (true)
    {
        // select variable to split
        IVariable *var = selectVariableToSplit();
        if (var == nullptr)
        {
            // all variables are fixed, we can stop
            return true;
        }
        // split on variable
        auto split = *var == var->lowerBound();
        decisions.push(split);
        propagate(split);

        // while there are violated constraints, we continue backtracking to the previous decision level
        while (areAnyConstraintsViolated())
        {
            if (getDecisionLevel() == 0)
            {
                // no decisions left, contradiction found
                return false;
            }
            // backtrack one decision level
            backtrack(getDecisionLevel() - 1);
        }
    }

    // should not be reachable
    return false;
}

IVariable *SolverContext::selectVariableToSplit()
{
    for (int i = 0; i < variables.size(); i++)
    {
        if (!variables[i]->isFixed())
        {
            return variables[i];
        }
    }
    return nullptr;
}

bool SolverContext::areAnyConstraintsViolated() const
{
    for (auto constraint : constraints)
    {
        if (constraint->isViolated())
        {
            return true;
        }
    }
    return false;
}

void SolverContext::propagate(AtomicConstraint ac)
{
    auto var = ac.getVariable();
    switch (ac.getOperator())
    {
    case Operator::GE:
        var->setLowerBound(*this, ac.getConstant());
        break;
    case Operator::LE:
        var->setUpperBound(*this, ac.getConstant());
        break;
    case Operator::EQ:
        var->setLowerBound(*this, ac.getConstant());
        var->setUpperBound(*this, ac.getConstant());
        break;
    case Operator::NE:
        var->remove(*this, ac.getConstant());
        break;
    }

    // TODO Propagating other constraints, would require propagation queue and such
}

void SolverContext::backtrack(unsigned int newLevel)
{
    if (newLevel >= decisions.size())
    {
        throw std::runtime_error("newLevel is too large");
    }

    AtomicConstraint lastDecision = decisions.top();
    while (decisions.size() > newLevel)
    {
        lastDecision = decisions.top();
        decisions.pop();
    }

    // rewind all variables to the state at the new decision level
    for (auto variable : variables)
    {
        variable->backtrack(newLevel);
    }
    propagate(lastDecision.invert());
}

unsigned int SolverContext::getDecisionLevel() const
{
    return decisions.size();
}

void SolverContext::addVariable(IVariable *variable)
{
    variables.push_back(variable);
}

void SolverContext::addConstraint(IConstraint *constraint)
{
    constraints.push_back(constraint);
}