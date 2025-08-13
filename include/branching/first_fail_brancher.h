#pragma once

#include "branching/brancher.h"

/// @brief Simple first-fail branching strategy
/// Chooses the variable with smallest domain, assigns its lower bound
class FirstFailBrancher : public IBrancher
{
public:
    std::optional<BranchingDecision> select_branch(const SolverContext &context) override;
};
