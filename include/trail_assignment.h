#pragma once

#include "trail.h"
#include "constraints/literal.h"
#include "variables/variable.h"

struct AssignmentTrailEntry
{
    Literal literal;    // The literal that caused the change
    DomainChange delta; // Change in domain

    AssignmentTrailEntry(Literal lit, DomainChange delta)
        : literal(lit), delta(delta)
    {
    }

    std::string to_string() const
    {
        return literal.to_string();
    }
};

template <>
inline bool Trail<AssignmentTrailEntry, Literal>::push(const Literal &lit)
{
    UpdateResult result = lit.var->update(lit.op, lit.constant);
    // Domain became empty
    if (!result)
    {
        return false;
    }
    // Domain changed, add to trail
    if (result.value().has_value())
    {
        const DomainChange &change = result.value().value();
        trail.emplace_back(AssignmentTrailEntry(lit, change));
    }
    return true;
}

template <>
inline Literal Trail<AssignmentTrailEntry, Literal>::backtrack(unsigned int target_level)
{
    assert_err(target_level < level_delimiter.size(), "Cannot backtrack to a non-existent level");
    size_t marker = level_delimiter[target_level];
    AssignmentTrailEntry last_entry = trail.back();
    while (trail.size() > marker)
    {
        last_entry = trail.back();
        // Revert previous state
        last_entry.literal.var->undo(last_entry.delta);
        trail.pop_back();
    }
    // Sync delimiter vector
    level_delimiter.resize(target_level);
    return last_entry.literal;
}
