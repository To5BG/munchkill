#include "variables/variable_single_holes.h"
#include "utils/asserts.h"

VariableSingleHoles::VariableSingleHoles(int lb, int ub)
    : lb(lb), ub(ub), holes({}), assigned(std::nullopt)
{
    assert_err(lb <= ub, "Inconsistent bounds");
}

void VariableSingleHoles::remove(int value)
{
    assert_warn(value >= lb && value <= ub, "Removing value outside current bounds");
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
    this->holes.insert(value);
}

void VariableSingleHoles::set_lower_bound(int value)
{
    assert_warn(value > lb, "Trying to relax the lower bound during propagation");
    this->lb = value;
    on_bound_change();
}

void VariableSingleHoles::set_upper_bound(int value)
{
    assert_warn(value < ub, "Trying to relax the upper bound during propagation");
    this->ub = value;
    on_bound_change();
}

void VariableSingleHoles::assign(int value)
{
    assert_warn(value >= lb && value <= ub && !holes.contains(value), "Assignment value not in domain");
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

void VariableSingleHoles::on_bound_change()
{
    int lb = this->lower_bound();
    int ub = this->upper_bound();
    assert_err(lb <= ub, "Inconsistent bounds");
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
