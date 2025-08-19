#pragma once
#include <spdlog/spdlog.h>
#include <exception>
#include <cstdlib>

#ifdef NDEBUG
// Release: just evaluate and return the expression
inline bool assert_warn(bool expr, const char *) noexcept
{
    return expr;
}
#else
// Debug: Also log a warning
inline bool assert_warn(bool expr, const char *msg)
{
    if (!expr)
        spdlog::warn("{}", msg);
    return expr;
}
#endif

inline void assert_err(bool expr, const char *msg)
{
    if (!expr)
    {
        spdlog::error("{}", msg);
        std::set_terminate([]
                           { std::_Exit(EXIT_FAILURE); });
        std::terminate();
    }
}
