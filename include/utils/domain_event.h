#pragma once

/// @brief Represents the type of domain modification that occurred on a variable
enum class DomainEvent
{
    Assign,     // Variable was assigned to a specific value
    Removal,    // A value was removed from the domain
    LowerBound, // Lower bound was tightened
    UpperBound  // Upper bound was tightened
};
