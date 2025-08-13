#include "variables/variable_single_holes.h"
#include "variables/variable.h"
#include "constraints/atomic_constraint.h"
#include "utils/operator.h"
#include "solver_context.h"
#include <optional>
#include <limits>

VariableSingleHoles::VariableSingleHoles(int lb, int ub)
    : lb(lb), ub(ub), holes({}), assigned(std::nullopt)
{
}

void VariableSingleHoles::remove(int value)
{
    if (value == lb)
    {
        while (holes.contains(value + 1))
            value++;
        set_lower_bound(value + 1);
    }
    else if (value == ub)
    {
        while (holes.contains(value - 1))
            value--;
        set_upper_bound(value - 1);
    }
    else
        // TODO Check if within bounds
        this->holes.insert(value);
}

void VariableSingleHoles::set_lower_bound(int value)
{
    // TODO Check if tightens
    this->lb = value;
    update_assigned_value();
}

void VariableSingleHoles::set_upper_bound(int value)
{
    // TODO Check if tightens
    this->ub = value;
    update_assigned_value();
}

void VariableSingleHoles::assign(int value)
{
    // TODO check if within bounds and not in holes
    this->assigned = value;
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
    switch (event)
    {
    case DomainEvent::Removal:
        if (value < lb)
            set_lower_bound(value);
        else if (value > ub)
            set_upper_bound(value);
        else
            holes.erase(value);
        break;
    case DomainEvent::LowerBound:
        lb = value;
        break;
    case DomainEvent::UpperBound:
        ub = value;
        break;
    case DomainEvent::Assign:
        break;
    }
    assigned = std::nullopt;
}

void VariableSingleHoles::update_assigned_value()
{
    int lb = this->lower_bound();
    int ub = this->upper_bound();
    if (lb == ub)
        assigned = lb;
}

std::optional<int> VariableSingleHoles::assigned_value() const
{
    return assigned;
}

bool VariableSingleHoles::is_fixed() const
{
    return assigned.has_value();
}
