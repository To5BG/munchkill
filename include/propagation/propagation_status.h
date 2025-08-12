#pragma once

/// @brief Status of a single propagation step
enum class PropagationStatus
{
    /// No propagation occurred
    NoChange,
    /// Some propagation occurred, should continue
    FixPoint,
    /// A conflict was detected during propagation
    Conflict
};
