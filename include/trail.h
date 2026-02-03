#pragma once

#include <vector>
#include <string>
#include "utils/asserts.h"

/// @brief Trail helper class to manage the sequence of domain modifications
template <typename T, typename U>
class Trail
{
private:
    std::vector<T> trail;
    std::vector<unsigned int> level_delimiter; // Marks where each decision level starts

public:
    Trail()
    {
        // Pre-allocate
        trail.reserve(128);
        level_delimiter.reserve(24);
    }
    ~Trail() = default;

    /// @brief Add a new entry to the trail (generic version)
    /// @param entry The entry to add
    /// @return false if the domain became empty, else true
    bool push(const U &entry)
    {
        trail.emplace_back(entry);
        return true;
    }

    /// @brief Increase the decision level
    void next_decision_level()
    {
        assert_err(level_delimiter.empty() || level_delimiter.back() < trail.size(),
                   "Cannot have an empty decision level");
        level_delimiter.push_back(trail.size());
    }

    /// @brief Backtrack to a specific decision level
    /// @param target_level The level to backtrack to
    /// @return The decision at the target level
    U backtrack(unsigned int target_level);

    /// @brief Get the current decision level
    unsigned int get_current_level() const { return level_delimiter.size(); }

    /// @brief Get the number of entries in the trail
    size_t size() const { return trail.size(); }

    /// @brief Clear the entire trail
    void clear()
    {
        trail.clear();
        level_delimiter.clear();
    }

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

    /// @brief Get the level delimiters
    std::vector<unsigned int> get_markers() const
    {
        return level_delimiter;
    }
};
