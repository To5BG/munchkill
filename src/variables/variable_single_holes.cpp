#include "variables/variable_single_holes.h"
#include "trail.h"

VariableSingleHoles::VariableSingleHoles(std::string id, int lb, int ub)
    : lb(lb), ub(ub), holes({})
{
    this->id = id;
}

UpdateResult VariableSingleHoles::remove(int value)
{
    if (value < lb || value > ub || holes.contains(value))
        return update_result::unchanged();
    int old_lb = lb, old_ub = ub;
    // Check for lower bound hole
    if (value == lb && !set_lower_bound(value + 1))
        return update_result::empty_domain();
    // Check for upper bound hole
    else if (value == ub && !set_upper_bound(value - 1))
        return update_result::empty_domain();
    holes.insert(value);
    return update_result::changed(old_lb, old_ub, value);
}

UpdateResult VariableSingleHoles::set_lower_bound(int value)
{
    if (value <= lb)
        return update_result::unchanged();
    // Make lb consistent - skip holes
    int old_lb = lb, old_ub = ub;
    while (holes.contains(value))
        value++;
    // Check consistency of update
    if (value > ub)
        return update_result::empty_domain();
    lb = value;
    return update_result::changed(old_lb, old_ub);
}

UpdateResult VariableSingleHoles::set_upper_bound(int value)
{
    if (value >= ub)
        return update_result::unchanged();
    // Make ub consistent - skip holes
    int old_lb = lb, old_ub = ub;
    while (holes.contains(value))
        value--;
    // Check consistency of update
    if (value < lb)
        return update_result::empty_domain();
    ub = value;
    return update_result::changed(old_lb, old_ub);
}

UpdateResult VariableSingleHoles::assign(int value)
{
    // Already assigned
    if (is_fixed())
        return update_result::unchanged();
    if (!is_valid(value))
        return update_result::empty_domain();
    int old_lb = lb, old_ub = ub;
    lb = ub = value;
    return update_result::changed(old_lb, old_ub);
}

void VariableSingleHoles::undo(DomainChange change)
{
    if (change.old_removed.has_value())
    {
        holes.erase(change.old_removed.value());
    }
    lb = change.old_lb;
    ub = change.old_ub;
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
    if (is_fixed())
        return lb;
    return std::nullopt;
}

bool VariableSingleHoles::is_fixed() const
{
    return lb == ub;
}

bool VariableSingleHoles::is_valid(int value) const
{
    if (value < lb || value > ub)
        return false;
    return !holes.contains(value);
}