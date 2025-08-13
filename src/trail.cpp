#include "trail.h"
#include "variables/variable.h"

Trail::Trail()
{
    level_delimiter.push_back(0); // Level 0 starts at position 0
}

void Trail::push(IVariable *variable, DomainEvent event, int value)
{
    trail.emplace_back(variable, event, value);
}

void Trail::next_decision_level()
{
    level_delimiter.push_back(trail.size()); // Mark where the new level starts
}

void Trail::backtrack(unsigned int target_level)
{
    size_t marker = level_delimiter[target_level];
    while (trail.size() > marker)
    {
        const TrailEntry &e = trail.back();
        // Revert previous state
        e.variable->undo(e.event, e.value);
        trail.pop_back();
    }
    // Sync delimiter vector
    level_delimiter.resize(target_level);
}

void Trail::clear()
{
    trail.clear();
    level_delimiter.clear();
    level_delimiter.push_back(0);
}
