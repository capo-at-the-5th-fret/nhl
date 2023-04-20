#pragma once

#include <cstdint>
#include <compare>
#include <iostream>
#include <functional>
#include <fmt/format.h>
#include "nhl/math/cmath.h"
#include "nhl/lottery/lottery.h"

namespace nhl::lottery
{
    class combination_value
    {
    public:
        using weak_type = std::uint16_t;
        using underlying_type = std::uint16_t;

        combination_value() = default;
        explicit constexpr combination_value(weak_type value) noexcept :
            value_(value) {}
        explicit constexpr combination_value(std::size_t one, std::size_t two,
            std::size_t three, std::size_t four) noexcept
        {
            value_ = static_cast<underlying_type>(
                (one << 12) |
                (two << 8) |
                (three << 4) |
                four
            );
        }

        auto operator<=>(combination_value const&) const = default;

        explicit constexpr operator weak_type() const noexcept
        {
            return value_;
        }

        constexpr bool ok() const noexcept
        {
            const auto one = this->one();
            const auto two = this->two();
            const auto three = this->three();
            const auto four = this->four();

            return (one >= 1 && one <= 14) &&
                (two >= 1 && two <= 14) &&
                (three >= 1 && three <= 14) &&
                (four >= 1 && four <= 14);
        }

        constexpr std::size_t one() const noexcept
        {
            return (value_ & 0b1111'0000'0000'0000) >> 12;
        }

        constexpr std::size_t two() const noexcept
        {
            return (value_ & 0b0000'1111'0000'0000) >> 8;
        }

        constexpr std::size_t three() const noexcept
        {
            return (value_ & 0b0000'0000'1111'0000) >> 4;
        }

        constexpr std::size_t four() const noexcept
        {
            return (value_ & 0b0000'0000'0000'1111);
        }

    private:
        underlying_type value_{ 0b0001'0010'0011'0100 }; // 1 2 3 4
    };

    template <typename F>
    F for_each_combination_value(F f)
    {
        math::for_each_combination<nhl::lottery::ball_count,
            nhl::lottery::combination_size>(
        [&](auto const& combo)
        {
            // combo is an array of indices, so add 1
            combination_value cv
            {
                combo[0] + 1,
                combo[1] + 1,
                combo[2] + 1,
                combo[3] + 1
            };

            f(cv);
        });

        return std::move(f);
    }

    inline std::ostream& operator<<(std::ostream& os,
        combination_value const& cv)
    {
        os << cv.one() << " " << cv.two() << " " << cv.three() << " " <<
            cv.four();
        return os;
    }
}

template <>
struct fmt::formatter<nhl::lottery::combination_value> :
    fmt::formatter<std::string>
{
    auto format(nhl::lottery::combination_value const& cv,
        fmt::format_context& ctx)
    {
        return formatter<std::string>::format(
            fmt::format("{} {} {} {}",
                cv.one(),
                cv.two(),
                cv.three(),
                cv.four()),
            ctx);
    }
};

template<>
struct std::hash<nhl::lottery::combination_value>
{
    std::size_t operator()(
        nhl::lottery::combination_value const& key) const noexcept
    {
        return std::hash<std::size_t>{}(static_cast<std::uint16_t>(key));
    }
};
