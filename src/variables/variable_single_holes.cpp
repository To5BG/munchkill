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
    int lb = std::numeric_limits<int>::min();
    for (const auto &shrink : domainShrinks)
    {
        if (shrink.first.getOperator() == Operator::GE)
        {
            lb = std::max(lb, shrink.first.getConstant());
        }
    }
    std::unordered_set<int> holes;
    for (const auto &shrink : domainShrinks)
    {
        if (shrink.first.getOperator() == Operator::NE)
        {
            holes.insert(shrink.first.getConstant());
        }
    }
    while (holes.contains(lb))
    {
        lb++;
    }
    return lb;
}

int VariableSingleHoles::upperBound() const
{
    int ub = std::numeric_limits<int>::max();
    for (const auto &shrink : domainShrinks)
    {
        if (shrink.first.getOperator() == Operator::LE)
        {
            ub = std::min(ub, shrink.first.getConstant());
        }
    }
    std::unordered_set<int> holes;
    for (const auto &shrink : domainShrinks)
    {
        if (shrink.first.getOperator() == Operator::NE)
        {
            holes.insert(shrink.first.getConstant());
        }
    }
    while (holes.contains(ub))
    {
        ub--;
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
