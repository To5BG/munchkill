#pragma once

#include "variables/variable.h"
#include "variables/domain_event.h"
#include <unordered_set>

class VariableSingleHoles : public IVariable
{

private:
    // int lb, ub;
    // std::unordered_set<int> holes;

    std::vector<std::pair<AtomicConstraint, int>> domainShrinks;

public:
    VariableSingleHoles(int lb, int ub);

    void remove(SolverContext &context, int value) override;
    void set_lower_bound(SolverContext &context, int value) override;
    void set_upper_bound(SolverContext &context, int value) override;
    int lower_bound() const override;
    int upper_bound() const override;
    std::optional<int> assigned_value() const override;
    bool is_fixed() const override;
    void backtrack(unsigned int newLevel) override;
    void undo(DomainEvent event, int value) override;
};