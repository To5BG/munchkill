#include "trail.h"
#include "variables/variable.h"
#include "utils/asserts.h"

Trail::Trail()
{
}

void Trail::push(IVariable *variable, DomainEvent event, int value)
{
    if (variable->update(event, value))
        trail.emplace_back(variable, event, value);
}

void Trail::next_decision_level()
{
    assert_err(level_delimiter.empty() || level_delimiter.back() < trail.size(), "Cannot have an empty decision level");
    level_delimiter.push_back(trail.size()); // Mark where the new level starts
}

TrailEntry Trail::backtrack(unsigned int target_level)
{
    assert_err(target_level < level_delimiter.size(), "Cannot backtrack to a non-existent level");
    size_t marker = level_delimiter[target_level];
    TrailEntry &last_entry = trail.back();
    while (trail.size() > marker)
    {
        last_entry = trail.back();
        // Revert previous state
        last_entry.variable->undo(last_entry.event, last_entry.value);
        trail.pop_back();
    }
    // Sync delimiter vector
    level_delimiter.resize(target_level);
    return last_entry;
}

void Trail::clear()
{
    trail.clear();
    level_delimiter.clear();
}
