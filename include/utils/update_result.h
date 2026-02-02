#pragma once

#include <expected>
#include <optional>

/// @brief Error type for when a domain operation results in an empty domain
struct EmptyDomain
{
};

/// @brief Information about a domain change: the old bounds before the update
struct DomainChange
{
    int old_lb;                     // Previous lower bound
    int old_ub;                     // Previous upper bound
    std::optional<int> old_removed; // Previously removed value, if any
};

/// @brief Result of a domain update operation using std::expected
/// Success: std::optional<DomainChange> where nullopt = no change, DomainChange = domain info for recovery
/// Failure: EmptyDomain indicating the domain became empty
using UpdateResult = std::expected<std::optional<DomainChange>, EmptyDomain>;

namespace update_result
{
    inline UpdateResult unchanged()
    {
        return std::optional<DomainChange>{std::nullopt};
    }

    inline UpdateResult changed(int old_lb, int old_ub)
    {
        return std::optional<DomainChange>{DomainChange{old_lb, old_ub, std::nullopt}};
    }

    inline UpdateResult changed(int old_lb, int old_ub, int old_removed)
    {
        return std::optional<DomainChange>{DomainChange{old_lb, old_ub, old_removed}};
    }

    inline UpdateResult empty_domain()
    {
        return std::unexpected<EmptyDomain>(EmptyDomain{});
    }
}
