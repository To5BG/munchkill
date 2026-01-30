#include <fmt/format.h>
#include "trail.h"
#include "variables/variable.h"
#include "utils/asserts.h"
#include "constraints/literal.h"

Trail::Trail()
{
}

bool Trail::push(Literal literal)
{
    UpdateResult result = literal.var->update(literal.op, literal.constant);
    // Domain became empty
    if (!result)
    {
        trail.emplace_back(literal);
        return false;
    }
    // Domain changed, add to trail
    if (result.value().has_value())
        trail.emplace_back(Literal(literal.var, literal.op, result.value().value()));
    return true;
}

void Trail::next_decision_level()
{
    assert_err(level_delimiter.empty() || level_delimiter.back() < trail.size(), "Cannot have an empty decision level");
    level_delimiter.push_back(trail.size()); // Mark where the new level starts
}

Literal Trail::backtrack(unsigned int target_level)
{
    assert_err(target_level < level_delimiter.size(), "Cannot backtrack to a non-existent level");
    size_t marker = level_delimiter[target_level];
    Literal &last_entry = trail.back();
    while (trail.size() > marker)
    {
        last_entry = trail.back();
        // Revert previous state
        last_entry.var->undo(last_entry.op, last_entry.constant);
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
