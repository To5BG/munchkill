#include "variables/variable_single_holes.h"
#include "variables/variable.h"
#include "constraints/atomic_constraint.h"
#include "utils/operator.h"
#include <limits>

VariableSingleHoles::VariableSingleHoles(int lb, int ub)
{
    domainShrinks.push_back({*this >= lb, 0});
    domainShrinks.push_back({*this <= ub, 0});
}

void VariableSingleHoles::remove(SolverContext &context, int value)
{
    domainShrinks.push_back({*this != value, context.getDecisionLevel()});
}

void VariableSingleHoles::setLowerBound(SolverContext &context, int value)
{
    domainShrinks.push_back({*this >= value, context.getDecisionLevel()});
}

void VariableSingleHoles::setUpperBound(SolverContext &context, int value)
{
    domainShrinks.push_back({*this <= value, context.getDecisionLevel()});
}

int VariableSingleHoles::lowerBound() const
{
}
void VariableSingleHoles::undo(DomainEvent event, int value)
{
    }
    return ub;
}

void VariableSingleHoles::backtrack(unsigned int newLevel)
{
    for (int i = domainShrinks.size() - 1; i >= 0; i--)
    {
        if (domainShrinks[i].second <= newLevel)
        {
            domainShrinks.resize(i + 1);
            return;
        }
    }
}

std::optional<int> VariableSingleHoles::assignedValue() const
{
    int lb = this->lowerBound();
    int ub = this->upperBound();
    if (lb == ub)
    {
        return lb;
    }
    return {};
}

bool VariableSingleHoles::isFixed() const
{
    return this->assignedValue().has_value();
}
