#pragma once

#include <queue>
#include <unordered_set>
#include <memory>

// Forward declarations
class IConstraint;

/// @brief Manages the order in which propagators are called for propagation
class PropagatorQueue
{
private:
    std::queue<IConstraint *> queue;
    std::unordered_set<IConstraint *> in_queue; // Track which propagators are already queued

public:
    PropagatorQueue() = default;

    /// @brief Add a propagator to the queue if it's not already queued
    /// @param propagator The propagator to add
    void enqueue(IConstraint *propagator);

    /// @brief Get the next propagator to run
    /// @return Next propagator or nullptr if queue is empty
    IConstraint *dequeue();

    /// @brief Check if the queue is empty
    /// @return True if queue is empty
    bool empty() const;

    /// @brief Clear the queue and reset all tracking
    void clear();

    /// @brief Get the number of propagators currently in the queue
    /// @return Number of propagators in queue
    size_t size() const;
};
