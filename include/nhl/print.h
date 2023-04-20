#pragma once

#include <iostream>
#include <fmt/format.h>

namespace temp
{
    template <typename... Args>
    void print(fmt::format_string<Args...> fmt, Args&&... args)
    {
        std::cout << fmt::format(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void println(fmt::format_string<Args...> fmt, Args&&... args)
    {
        std::cout << fmt::format(fmt, std::forward<Args>(args)...) << "\n";
    }
}
