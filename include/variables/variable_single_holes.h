#pragma once

#include "variables/variable.h"
#include <unordered_set>

class VariableSingleHoles : public IVariable
{

private:
    // int lb, ub;
    // std::unordered_set<int> holes;

    std::vector<std::pair<AtomicConstraint, int>> domainShrinks;

public:
    VariableSingleHoles(int lb, int ub);

    void remove(SolverContext& context,int value) override;
    void setLowerBound(SolverContext& context, int value) override;
    void setUpperBound(SolverContext& context, int value) override;
    int lowerBound() const override;
    int upperBound() const override;
    std::optional<int> assignedValue() const override;
    bool isFixed() const override;
    void backtrack(unsigned int newLevel) override;
};