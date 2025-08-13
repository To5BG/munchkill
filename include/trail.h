#pragma once

#include <vector>
#include <stack>
#include "variables/domain_event.h"

class IVariable;

/// @brief Represents a single entry on the trail
struct TrailEntry
{
    IVariable *variable; // The variable that was modified
    DomainEvent event;   // The type of modification
    int value;           // The value involved (old value for bounds, removed value for removal)

    TrailEntry(IVariable *var, DomainEvent evt, int val)
        : variable(var), event(evt), value(val) {}
};

/// @brief Trail helper class to manage the sequence of domain modifications
/// This will be extended later to handle propagation levels and other features
class Trail
{
private:
    std::vector<TrailEntry> trail;
    std::vector<unsigned int> level_delimiter; // Marks where each decision level starts

public:
    Trail();

    /// @brief Add a new entry to the trail
    /// @param variable The variable being modified
    /// @param event The type of domain event
    /// @param value The value involved in the modification
    void push(IVariable *variable, DomainEvent event, int value);

    /// @brief Increase the decision level
    void next_decision_level();

    /// @brief Backtrack to a specific decision level
    /// @param target_level The level to backtrack to
    void backtrack(unsigned int target_level);

    /// @brief Get the current decision level
    unsigned int get_current_level() const { return level_delimiter.size() - 1; }

    /// @brief Get the number of entries in the trail
    size_t size() const { return trail.size(); }

    /// @brief Clear the entire trail
    void clear();
};
