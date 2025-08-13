#include "variables/variable_single_holes.h"
#include "variables/variable.h"
#include "constraints/atomic_constraint.h"
#include "utils/operator.h"
#include "solver_context.h"
#include <limits>

VariableSingleHoles::VariableSingleHoles(int lb, int ub)
{
    this->lb = lb;
    this->ub = ub;
    this->holes = {};
}

void VariableSingleHoles::remove(SolverContext &context, int value)
{
    this->holes.insert(value);
}

void VariableSingleHoles::set_lower_bound(SolverContext &context, int value)
{
    this->lb = value;
}

void VariableSingleHoles::set_upper_bound(SolverContext &context, int value)
{
    this->ub = value;
}

int VariableSingleHoles::lower_bound() const
{
    return this->lb;
}

int VariableSingleHoles::upper_bound() const
{
    return this->ub;
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

std::optional<int> VariableSingleHoles::assigned_value() const
{
    int lb = this->lower_bound();
    int ub = this->upper_bound();
    if (lb == ub)
    {
        return lb;
    }
    return {};
}

bool VariableSingleHoles::is_fixed() const
{
    return this->assignedValue().has_value();
}
