#pragma once

#include "variables/variable.h"
#include <unordered_set>
#include <optional>
#include "variables/variable_iter.h"

class VariableSingleHoles : public IVariable, public Iterable<VariableSingleHoles>
{

private:
    int lb, ub;
    std::optional<int> assigned;
    std::unordered_set<int> holes;

    UpdateResult remove(int value) override;
    UpdateResult set_lower_bound(int value) override;
    UpdateResult set_upper_bound(int value) override;
    UpdateResult assign(int value) override;

    /// @brief A helper to check bound consistency and update assigned if needed
    /// @return True if the bounds are consistent, false otherwise
    bool on_bound_change(int lb, int ub);

public:
    VariableSingleHoles(std::string id, int lb, int ub);

    void undo(DomainEvent event, int value) override;

    int lower_bound() const override;
    int upper_bound() const override;
    std::optional<int> assigned_value() const override;
    bool is_fixed() const override;
    bool is_valid(int value) const override;
};