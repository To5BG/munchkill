#pragma once

#include <vector>
#include <string>
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

    /// @brief Get a string representation of the trail
    std::string to_string() const
    {
        std::string repr;
        repr += "{";
        // Go through each level based on delimiters
        size_t current_level = 0;
        size_t next_level_start = (level_delimiter.empty() ? trail.size() : level_delimiter[0]);
        for (size_t i = 0; i < trail.size(); ++i)
        {
            if (i == next_level_start)
            {
                repr += " | ";
                current_level++;
                if (current_level < level_delimiter.size())
                    next_level_start = level_delimiter[current_level];
                else
                    next_level_start = trail.size();
            }
            repr += trail[i].to_string();
        }
        repr += "}";
        return repr;
    }
};
