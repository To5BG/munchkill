#pragma once

#include "branching/brancher.h"

/// @brief Basic Depth-First Search brancher
/// Selects the first unfixed variable and tries its minimum value first
class DFSBrancher : public IBrancher
{
public:
    std::optional<Decision> next(const Solver &context) override;
};
