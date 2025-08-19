#pragma once

#include "variables/variable.h"
#include <unordered_set>
#include <optional>

class VariableSingleHoles : public IVariable
{

private:
    int lb, ub;
    std::optional<int> assigned;
    std::unordered_set<int> holes;

    bool remove(int value) override;
    bool set_lower_bound(int value) override;
    bool set_upper_bound(int value) override;
    bool assign(int value) override;

    void on_bound_change();

public:
    VariableSingleHoles(int lb, int ub);

    void undo(DomainEvent event, int value) override;

    int lower_bound() const override;
    int upper_bound() const override;
    std::optional<int> assigned_value() const override;
    bool is_fixed() const override;
};