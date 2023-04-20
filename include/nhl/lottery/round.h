#pragma once

#include <iostream>
#include <fmt/format.h>
#include "nhl/lottery/lottery.h"

namespace nhl::lottery
{
    class round_number
    {
    public:
        using weak_type = int;
        using underlying_type = std::uint8_t;
    
        round_number() = default;
        explicit constexpr round_number(weak_type value) noexcept :
            value_(static_cast<underlying_type>(value)) {}

        auto operator<=>(round_number const&) const = default;

        constexpr round_number operator+() const noexcept;
        constexpr round_number operator-() const noexcept;
        constexpr round_number& operator++() noexcept;
        constexpr round_number operator++(int) noexcept;
        constexpr round_number& operator--() noexcept;
        constexpr round_number operator--(int) noexcept;
        constexpr round_number& operator+=(round_number const& rhs) noexcept;
        constexpr round_number& operator-=(round_number const& rhs) noexcept;
        constexpr round_number& operator*=(round_number const& rhs) noexcept;
        constexpr round_number& operator*=(weak_type rhs) noexcept;
        constexpr round_number& operator/=(round_number const& rhs) noexcept;
        constexpr round_number& operator/=(weak_type rhs) noexcept;
        constexpr round_number& operator%=(round_number const& rhs) noexcept;
        constexpr round_number& operator%=(weak_type rhs) noexcept;
    
        explicit constexpr operator weak_type() const noexcept
        {
            return value_;
        }
    
        constexpr bool ok() const noexcept
        {
            return value_ >= static_cast<weak_type>((round_number::min)()) &&
                value_ <= static_cast<weak_type>((round_number::max)());
        }
    
        static constexpr round_number (min)() noexcept
        {
            return round_number{ 1 };
        }
    
        static constexpr round_number (max)() noexcept
        {
            return round_number{ 2 };
        }
    
    private:
        underlying_type value_{ 1 };
    };
    
    constexpr round_number operator+(round_number const& lhs, round_number const& rhs) noexcept;
    constexpr round_number operator-(round_number const& lhs, round_number const& rhs) noexcept;
    constexpr round_number operator*(round_number const& lhs, round_number const& rhs) noexcept;
    constexpr round_number operator*(round_number const& lhs, typename round_number::weak_type rhs) noexcept;
    constexpr round_number operator/(round_number const& lhs, round_number const& rhs) noexcept;
    constexpr round_number operator/(round_number const& lhs, typename round_number::weak_type rhs) noexcept;
    constexpr round_number operator%(round_number const& lhs, round_number const& rhs) noexcept;
    constexpr round_number operator%(round_number const& lhs, typename round_number::weak_type rhs) noexcept;
    
    constexpr round_number round_number::operator+() const noexcept
    {
        return *this;
    }
    
    constexpr round_number round_number::operator-() const noexcept
    {
        return round_number{ -value_ };
    }
    
    constexpr round_number& round_number::operator++() noexcept
    {
        ++value_;
        return *this;
    }
    
    constexpr round_number round_number::operator++(int) noexcept
    {
        auto tmp(*this);
        ++(*this);
        return tmp;
    }
    
    constexpr round_number& round_number::operator--() noexcept
    {
        --value_;
        return *this;
    }
    
    constexpr round_number round_number::operator--(int) noexcept
    {
        auto tmp(*this);
        --(*this);
        return tmp;
    }
    
    constexpr round_number& round_number::operator+=(round_number const& rhs) noexcept
    {
        *this = *this + rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator-=(round_number const& rhs) noexcept
    {
        *this = *this - rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator*=(round_number const& rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator*=(typename round_number::weak_type rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator/=(round_number const& rhs) noexcept
    {
        *this = *this / rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator/=(typename round_number::weak_type rhs) noexcept
    {
        *this = *this / rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator%=(round_number const& rhs) noexcept
    {
        *this = *this % rhs;
        return *this;
    }
    
    constexpr round_number& round_number::operator%=(typename round_number::weak_type rhs) noexcept
    {
        *this = *this % rhs;
        return *this;
    }
    
    constexpr round_number operator+(round_number const& lhs, round_number const& rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) + static_cast<weak_type>(rhs) };
    }
    
    constexpr round_number operator-(round_number const& lhs, round_number const& rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) - static_cast<weak_type>(rhs) };
    }
    
    constexpr round_number operator*(round_number const& lhs, round_number const& rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) * static_cast<weak_type>(rhs) };
    }
    
    constexpr round_number operator*(typename round_number::weak_type lhs, round_number const& rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ lhs * static_cast<weak_type>(rhs) };
    }
    
    constexpr round_number operator*(round_number const& lhs, typename round_number::weak_type rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) * rhs };
    }
    
    constexpr round_number operator/(round_number const& lhs, round_number const& rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) / static_cast<weak_type>(rhs) };
    }
    
    constexpr round_number operator/(round_number const& lhs, typename round_number::weak_type rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) / rhs };
    }
    
    constexpr round_number operator%(round_number const& lhs, round_number const& rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) % static_cast<weak_type>(rhs) };
    }
    
    constexpr round_number operator%(round_number const& lhs, typename round_number::weak_type rhs) noexcept
    {
        using weak_type = typename round_number::weak_type;
        return round_number{ static_cast<weak_type>(lhs) % rhs };
    }

    inline std::ostream& operator<<(std::ostream& os, round_number const& n)
    {
        os << static_cast<int>(n);
        return os;
    }

    inline constexpr std::array rounds = []()
    {
        std::array<round_number, lottery_rounds> ret;
        for (std::size_t i = 0; i < ret.size(); ++i)
        {
            ret[i] = round_number{ static_cast<int>(i + 1) };
        }
        return ret;
    }();
}

template <>
struct fmt::formatter<nhl::lottery::round_number> : fmt::formatter<int>
{
    auto format(nhl::lottery::round_number const& n, fmt::format_context& ctx)
    {
        return formatter<int>::format(static_cast<int>(n), ctx);
    }
};

template<>
struct std::hash<nhl::lottery::round_number>
{
    std::size_t operator()(nhl::lottery::round_number const& key) const noexcept
    {
        return std::hash<int>{}(static_cast<int>(key));
    }
};
