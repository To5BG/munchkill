#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "constraints/implementations/not_equals.h"

int main()
{
    // Print using fmt
    fmt::print("Hello, {}!\n", "world");
    // Print using spdlog
    spdlog::info("This is an info message from spdlog.");
    spdlog::warn("This is a warning.");
    spdlog::error("This is an error message.");
    // New C++23 feature (optional): deducing this
    auto greet = [](std::string_view name)
    {
        return fmt::format("Hi, {}! Welcome to C++23 🎉", name);
    };
    
    fmt::print("{}\n", greet("Munchkill"));
    return 0;
}
