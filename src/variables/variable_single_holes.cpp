#include "variables/variable_single_holes.h"
#include "utils/asserts.h"

VariableSingleHoles::VariableSingleHoles(std::string id, int lb, int ub)
    : lb(lb), ub(ub), holes({})
{
    this->id = id;
    on_bound_change(lb, ub);
}

UpdateResult VariableSingleHoles::remove(int value)
{
    if (value < lb || value > ub || holes.contains(value))
        return update_result::unchanged();
    // Check for lower bound hole
    if (value == lb && !set_lower_bound(value + 1))
        return update_result::empty_domain();
    // Check for upper bound hole
    else if (value == ub && !set_upper_bound(value - 1))
        return update_result::empty_domain();
    holes.insert(value);
    return update_result::changed(value);
}

UpdateResult VariableSingleHoles::set_lower_bound(int value)
{
    if (value <= lb)
        return update_result::unchanged();
    // Make lb consistent - skip holes
    int old_lb = lb;
    while (holes.contains(value))
        value++;
    // Check consistency or update
    if (!on_bound_change(value, ub))
        return update_result::empty_domain();
    lb = value;
    return update_result::changed(old_lb);
}

UpdateResult VariableSingleHoles::set_upper_bound(int value)
{
    if (value >= ub)
        return update_result::unchanged();
    // Make ub consistent - skip holes
    int old_ub = ub;
    while (holes.contains(value))
        value--;
    // Check consistency or update
    if (!on_bound_change(lb, value))
        return update_result::empty_domain();
    ub = value;
    return update_result::changed(old_ub);
}

UpdateResult VariableSingleHoles::assign(int value)
{
    if (!is_valid(value))
        return update_result::empty_domain();
    if (assigned == value)
        return update_result::unchanged();
    assigned = value;
    return update_result::changed(value);
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

bool VariableSingleHoles::is_valid(int value) const
{
    if (value < lb || value > ub)
        return false;
    return !holes.contains(value);
}

bool VariableSingleHoles::on_bound_change(int lb, int ub)
{
    if (lb > ub)
        return false;
    // iff lb < ub
    if (lb != ub)
        return true;
    if (!holes.contains(lb))
    {
        assigned = lb;
        return true;
    }
    return false;
}