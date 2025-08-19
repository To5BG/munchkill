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

public:
    VariableSingleHoles(int lb, int ub);

    void remove(int value) override;
    void set_lower_bound(int value) override;
    void set_upper_bound(int value) override;
    void assign(int value) override;
    void undo(DomainEvent event, int value) override;

    int lower_bound() const override;
    int upper_bound() const override;
    std::optional<int> assigned_value() const override;
    bool is_fixed() const override;

    void on_bound_change();
};