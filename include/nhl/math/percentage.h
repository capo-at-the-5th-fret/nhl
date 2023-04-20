#pragma once

#include <concepts>
#include <compare>
#include <iostream>
#include <fmt/format.h>

namespace math
{
    // FIX: The formatter to include % sign or not? number vs. ratio format type?
    enum class percent_rep : std::uint8_t
    {
        number, // number relative to 100 (per cent means per hundred; i.e. 25.5%
                // would be represented by the number 25.5)
        ratio   // decimal point representation (/ 100 form; for 25.5%, this
                // would be .255)
    };

    template <std::floating_point Rep>
    class percentage_t
    {
    public:
        using underlying_type = Rep;

        percentage_t() = default;
        explicit constexpr percentage_t(Rep value,
            percent_rep rep = percent_rep::number) noexcept
            : value_
            {
                (rep == percent_rep::ratio) ?
                static_cast<Rep>(value * 100.0) :
                value
            }
        {
        }

        // FIX: cast for value_
        template <typename T1, typename T2>
        explicit constexpr percentage_t(T1 const& t1, T2 const& t2)
            : value_{static_cast<Rep>(
                static_cast<std::common_type_t<T1,Rep>>(t1) /
                static_cast<std::common_type_t<T2,Rep>>(t2)) * 100.0}
        {
        }

        auto operator<=>(percentage_t const&) const = default;

        constexpr percentage_t operator+() const noexcept
        {
            return *this;
        }
        constexpr percentage_t operator-() const noexcept
        {
            return percentage_t{ -value_ };
        }

        explicit constexpr operator Rep() const noexcept
        {
            return value_;
        }

        constexpr Rep value() const noexcept
        {
            return value_;
        }

        constexpr Rep to_ratio() const noexcept
        {
            return value_ / 100.0;
        }

    private:
        Rep value_{ 0 };
    };

    using percentage = percentage_t<double>;

    // what percent is x over y?
    template <std::floating_point PercentType = double,
              typename T1,
              typename T2>
    constexpr percentage_t<PercentType> percent(T1 const& num, T2 const& den)
    {
        return percentage_t<PercentType>{ num, den };
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, percentage_t<T> const& p)
    {
        os << static_cast<T>(p) << "%";
        return os;
    }
}

template <std::floating_point T>
struct fmt::formatter<math::percentage_t<T>> :
    fmt::formatter<typename math::percentage_t<T>::weak_type>
{
    auto format(math::percentage_t<T> const& pct, fmt::format_context& ctx)
    {
        return formatter<typename math::percentage_t<T>::weak_type>::format(
            static_cast<typename math::percentage_t<T>::weak_type>(pct), ctx);
    }
};

namespace math
{
    inline namespace literals
    {
        inline namespace math_literals
        {
            consteval percentage operator""_pct(unsigned long long value)
            {
                return percentage{static_cast<double>(value)};
            }

            consteval percentage operator""_pct(long double value)
            {
                return percentage{static_cast<double>(value)};
            }
        }
    }
}
