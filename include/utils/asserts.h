#pragma once
#include <spdlog/spdlog.h>
#include <exception>
#include <cstdlib>

#ifndef NDEBUG
#define assert_warn(expr, msg)       \
    do                               \
    {                                \
        if (!(expr))                 \
        {                            \
            spdlog::warn("{}", msg); \
        }                            \
    } while (0)
#else
#define assert_warn(expr, msg) ((void)0)
#endif

inline void assert_err(bool expr, const char *msg)
{
    if (!(expr))
    {
        spdlog::error("{}", msg);
        std::set_terminate([]
                           { std::_Exit(EXIT_FAILURE); });
        std::terminate();
    }
}
