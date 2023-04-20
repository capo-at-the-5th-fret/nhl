#pragma once

#include <cstdint>
#include <compare>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <fmt/format.h>
#include "nhl/lottery/lottery.h"

namespace nhl::lottery
{
    class ball
    {
    public:
        using weak_type = int;
        using underlying_type = std::int8_t;

        ball() = default;
        explicit constexpr ball(weak_type value) noexcept :
            value_(static_cast<underlying_type>(value)) {}

        auto operator<=>(ball const&) const = default;

        explicit constexpr operator weak_type() const noexcept
        {
            return value_;
        }

        constexpr bool ok() const noexcept
        {
            return std::cmp_greater_equal(value_,
                    static_cast<weak_type>((ball::min)())) &&
                std::cmp_less_equal(value_,
                    static_cast<weak_type>((ball::max)()));
        }

        static constexpr ball (min)() noexcept
        {
            return ball{ 1 };
        }

        static constexpr ball (max)() noexcept
        {
            return ball{ 14 };
        }

    private:
        underlying_type value_{ 1 };
    };

    std::ostream& operator<<(std::ostream& os, ball const& b)
    {
        os << static_cast<int>(b);
        return os;
    }

    inline constexpr std::array balls = []()
    {
        std::array<ball, ball_count> ret;
        for (std::size_t i = 0; i < ball_count; ++i)
        {
            ret[i] = ball{ static_cast<int>(i) + 1 };
        }
        return ret;
    }();

    static_assert(balls.size() == ball_count);
// #if __cpp_lib_ranges
//     static_assert(std::ranges::is_sorted(balls));
//     static_assert(std::ranges::adjacent_find(balls) ==
//         std::ranges::end(balls));
// #endif

}

template <>
struct fmt::formatter<nhl::lottery::ball> : fmt::formatter<int>
{
    auto format(nhl::lottery::ball const& b, fmt::format_context& ctx) const
    {
        return fmt::formatter<int>::format(static_cast<int>(b), ctx);
    }
};
