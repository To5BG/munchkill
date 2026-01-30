#pragma once

#include <vector>
#include <string>
#include "utils/domain_event.h"
#include "utils/update_result.h"
#include "constraints/literal.h"

// Forward declarations
class IVariable;

/// @brief Trail helper class to manage the sequence of domain modifications
/// This will be extended later to handle propagation levels and other features
class Trail
{
private:
    std::vector<Literal> trail;
    std::vector<unsigned int> level_delimiter; // Marks where each decision level starts

public:
    Trail();

    /// @brief Add a new entry to the trail
    /// @param literal The literal representing the domain modification
    /// @return false if the domain became empty, else true
    bool push(Literal literal);

    /// @brief Increase the decision level
    void next_decision_level();

    /// @brief Backtrack to a specific decision level
    /// @param target_level The level to backtrack to
    /// @return The decision at the target level
    Literal backtrack(unsigned int target_level);

    /// @brief Get the current decision level
    unsigned int get_current_level() const { return level_delimiter.size(); }

    /// @brief Get the number of entries in the trail
    size_t size() const { return trail.size(); }

    /// @brief Clear the entire trail
    void clear();

    /// @brief Get a string representation of the trail (for debugging)
    std::string to_string() const;
};
