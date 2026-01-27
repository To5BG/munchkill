#pragma once

#include <expected>
#include <optional>

/// @brief Error type for when a domain operation results in an empty domain
struct EmptyDomain
{
};

/// @brief Result of a domain update operation using std::expected
/// Success: std::optional<int> where nullopt = no change, int = trail value
/// Failure: EmptyDomain indicating the domain became empty
using UpdateResult = std::expected<std::optional<int>, EmptyDomain>;

namespace update_result
{
    inline UpdateResult unchanged()
    {
        return std::optional<int>{std::nullopt};
    }

    inline UpdateResult changed(int trail_value)
    {
        return std::optional<int>{trail_value};
    }

    inline UpdateResult empty_domain()
    {
        return std::unexpected<EmptyDomain>(EmptyDomain{});
    }
}
