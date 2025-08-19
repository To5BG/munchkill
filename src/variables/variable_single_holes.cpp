#include "variables/variable_single_holes.h"
#include "utils/asserts.h"

VariableSingleHoles::VariableSingleHoles(int lb, int ub)
    : lb(lb), ub(ub), holes({})
{
    on_bound_change();
}

bool VariableSingleHoles::remove(int value)
{
    if (!assert_warn(value >= lb && value <= ub, "Removing value outside current bounds"))
        return false;
    // Check for holes on bounds
    if (value == lb)
        set_lower_bound(value + 1);
    else if (value == ub)
        set_upper_bound(value - 1);
    holes.insert(value);
    return true;
}

bool VariableSingleHoles::set_lower_bound(int value)
{
    if (!assert_warn(value > lb, "Trying to relax the lower bound during propagation"))
        return false;
    // Make lb consistent - skip holes
    while (holes.contains(value))
        value++;
    lb = value;
    on_bound_change();
    return true;
}

bool VariableSingleHoles::set_upper_bound(int value)
{
    if (!assert_warn(value < ub, "Trying to relax the upper bound during propagation"))
        return false;
    // Make ub consistent - skip holes
    while (holes.contains(value))
        value--;
    ub = value;
    on_bound_change();
    return true;
}

bool VariableSingleHoles::assign(int value)
{
    if (!assert_warn(value >= lb && value <= ub && !holes.contains(value), "Assignment value not in domain"))
        return false;
    assigned = value;
    return true;
}

void VariableSingleHoles::undo(DomainEvent event, int value)
{
    switch (event)
    {
    case DomainEvent::Removal:
        if (value < lb)
            lb = value;
        else if (value > ub)
            ub = value;
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

int VariableSingleHoles::lower_bound() const
{
    return lb;
}

int VariableSingleHoles::upper_bound() const
{
    return ub;
}

std::optional<int> VariableSingleHoles::assigned_value() const
{
    return assigned;
}

bool VariableSingleHoles::is_fixed() const
{
    return assigned.has_value();
}

void VariableSingleHoles::on_bound_change()
{
    int lb = lower_bound();
    int ub = upper_bound();
    assert_err(lb <= ub, "Inconsistent bounds");
    if (lb == ub)
        assigned = lb;
}