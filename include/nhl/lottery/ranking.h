#pragma once

#include <cstdint>
#include <stdexcept>
#include <compare>
#include <array>
#include <numeric>
#include <algorithm>
#include "nhl/lottery/lottery.h"

namespace nhl::lottery
{
#if 0
    class ranking
    {
    public:
        using weak_type = int;
        using underlying_type = std::uint8_t;
    
        ranking() = default;
        explicit constexpr ranking(weak_type value) noexcept :
            value_(static_cast<underlying_type>(value)) {}
    
        auto operator<=>(ranking const&) const = default;
    
        constexpr ranking operator+() const noexcept;
        constexpr ranking operator-() const noexcept;
        constexpr ranking& operator++() noexcept;
        constexpr ranking operator++(int) noexcept;
        constexpr ranking& operator--() noexcept;
        constexpr ranking operator--(int) noexcept;
        constexpr ranking& operator+=(ranking const& rhs) noexcept;
        constexpr ranking& operator-=(ranking const& rhs) noexcept;
        constexpr ranking& operator*=(ranking const& rhs) noexcept;
        constexpr ranking& operator*=(weak_type rhs) noexcept;
        constexpr ranking& operator/=(ranking const& rhs) noexcept;
        constexpr ranking& operator/=(weak_type rhs) noexcept;
        constexpr ranking& operator%=(ranking const& rhs) noexcept;
        constexpr ranking& operator%=(weak_type rhs) noexcept;
    
        explicit constexpr operator weak_type() const noexcept
        {
            return value_;
        }
    
        constexpr bool ok() const noexcept
        {
            return value_ >= static_cast<weak_type>((ranking::min)()) &&
                value_ <= static_cast<weak_type>((ranking::max)());
        }
    
        static constexpr ranking (min)() noexcept
        {
            return ranking{ 1 };
        }
    
        static constexpr ranking (max)() noexcept
        {
            return ranking{ 16 };
        }
    
    private:
        underlying_type value_{ 1 };
    };
    
    constexpr ranking operator+(ranking const& lhs, ranking const& rhs) noexcept;
    constexpr ranking operator-(ranking const& lhs, ranking const& rhs) noexcept;
    constexpr ranking operator*(ranking const& lhs, ranking const& rhs) noexcept;
    constexpr ranking operator*(ranking const& lhs, typename ranking::weak_type rhs) noexcept;
    constexpr ranking operator/(ranking const& lhs, ranking const& rhs) noexcept;
    constexpr ranking operator/(ranking const& lhs, typename ranking::weak_type rhs) noexcept;
    constexpr ranking operator%(ranking const& lhs, ranking const& rhs) noexcept;
    constexpr ranking operator%(ranking const& lhs, typename ranking::weak_type rhs) noexcept;
    
    constexpr ranking ranking::operator+() const noexcept
    {
        return *this;
    }
    
    constexpr ranking ranking::operator-() const noexcept
    {
        return ranking{ -value_ };
    }
    
    constexpr ranking& ranking::operator++() noexcept
    {
        ++value_;
        return *this;
    }
    
    constexpr ranking ranking::operator++(int) noexcept
    {
        auto tmp(*this);
        ++(*this);
        return tmp;
    }
    
    constexpr ranking& ranking::operator--() noexcept
    {
        --value_;
        return *this;
    }
    
    constexpr ranking ranking::operator--(int) noexcept
    {
        auto tmp(*this);
        --(*this);
        return tmp;
    }
    
    constexpr ranking& ranking::operator+=(ranking const& rhs) noexcept
    {
        *this = *this + rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator-=(ranking const& rhs) noexcept
    {
        *this = *this - rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator*=(ranking const& rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator*=(typename ranking::weak_type rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator/=(ranking const& rhs) noexcept
    {
        *this = *this / rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator/=(typename ranking::weak_type rhs) noexcept
    {
        *this = *this / rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator%=(ranking const& rhs) noexcept
    {
        *this = *this % rhs;
        return *this;
    }
    
    constexpr ranking& ranking::operator%=(typename ranking::weak_type rhs) noexcept
    {
        *this = *this % rhs;
        return *this;
    }
    
    constexpr ranking operator+(ranking const& lhs, ranking const& rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) + static_cast<weak_type>(rhs) };
    }
    
    constexpr ranking operator-(ranking const& lhs, ranking const& rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) - static_cast<weak_type>(rhs) };
    }
    
    constexpr ranking operator*(ranking const& lhs, ranking const& rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) * static_cast<weak_type>(rhs) };
    }
    
    constexpr ranking operator*(typename ranking::weak_type lhs, ranking const& rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ lhs * static_cast<weak_type>(rhs) };
    }
    
    constexpr ranking operator*(ranking const& lhs, typename ranking::weak_type rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) * rhs };
    }
    
    constexpr ranking operator/(ranking const& lhs, ranking const& rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) / static_cast<weak_type>(rhs) };
    }
    
    constexpr ranking operator/(ranking const& lhs, typename ranking::weak_type rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) / rhs };
    }
    
    constexpr ranking operator%(ranking const& lhs, ranking const& rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) % static_cast<weak_type>(rhs) };
    }
    
    constexpr ranking operator%(ranking const& lhs, typename ranking::weak_type rhs) noexcept
    {
        using weak_type = typename ranking::weak_type;
        return ranking{ static_cast<weak_type>(lhs) % rhs };
    }

    inline constexpr std::array rankings =
    {
        ranking{ 1 },
        ranking{ 2 },
        ranking{ 3 },
        ranking{ 4 },
        ranking{ 5 },
        ranking{ 6 },
        ranking{ 7 },
        ranking{ 8 },
        ranking{ 9 },
        ranking{ 10 },
        ranking{ 11 },
        ranking{ 12 },
        ranking{ 13 },
        ranking{ 14 },
        ranking{ 15 },
        ranking{ 16 }
    };
#endif

    inline constexpr std::array rankings = []()
    {
        std::array<int, rankings_count> ret;
        //std::ranges::iota(ret, 1);
        std::iota(ret.begin(), ret.end(), 1);
        return ret;
    }();
    static_assert(rankings.size() == rankings_count);
#if __cpp_lib_ranges
    static_assert(std::ranges::is_sorted(rankings));
    static_assert(std::ranges::adjacent_find(rankings) ==
        std::ranges::end(rankings));
#endif
}

#if 0
namespace nhl::lottery
{
    inline namespace lottery_literals
    {
        consteval ranking operator""_ranking(
            unsigned long long value)
        {
            ranking ret{ static_cast<int>(value) };
            if (!ret.ok())
            {
                throw std::out_of_range("The ranking value is out of range");
            }
            return ret;
        }
    }
}

namespace nhl
{
    inline namespace literals
    {
        namespace lottery_literals = nhl::lottery::lottery_literals;
    }
}
#endif
