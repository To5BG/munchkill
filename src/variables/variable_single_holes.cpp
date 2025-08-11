#include "variables/variable_single_holes.h"
#include "variables/variable.h"
#include "constraints/implementations/atomic_constraint.h"
#include "utils/operator.h"

VariableSingleHoles::VariableSingleHoles(int lb, int ub) :
    lb(lb),
    ub(ub)
{
    // do nothing
}

void VariableSingleHoles::remove(SolverContext& context, int value)
{
    // TODO
    domainShrinks.push_back(AtomicConstraint(this, Operator::NE, value));
    this->holes.insert(value);
}

void VariableSingleHoles::setLowerBound(SolverContext& context, int value)
{
    // TODO
    domainShrinks.push_back(AtomicConstraint(this, Operator::GE, value));
    this->lb = std::max(this->lb, value);
}

void VariableSingleHoles::setUpperBound(SolverContext& context, int value)
{
    // TODO
    domainShrinks.push_back(AtomicConstraint(this, Operator::LE, value));
    this->ub = std::max(this->ub, value);
}

int VariableSingleHoles::lowerBound() const
{
    return this->lb;
}

int VariableSingleHoles::upperBound() const
{
    return this->ub;
}

void VariableSingleHoles::newDecisionLevel() {
    // TODO: Implement
    //decisionLevelStarts.push_back(domainShrinks.size());
}

void VariableSingleHoles::rewindDecisionLevel(unsigned int newLevel) {
    // TODO: Implement
    // if (newLevel >= decisionLevelStarts.size()) {
    //     throw "newLevel is too large";
    // }

    // recalculate bounds, not optimal right now
}

std::optional<int> VariableSingleHoles::assignedValue() const 
{
    // TODO: Implement
    return {};
}

bool VariableSingleHoles::isFixed() const 
{
    // TODO: Implement
    return false;
}
