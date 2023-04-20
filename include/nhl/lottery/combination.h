
#pragma once

#include <array>
#include <algorithm>
#include <fmt/format.h>
#include "nhl/lottery/lottery.h"
#include "nhl/lottery/ball.h"
#include "nhl/lottery/combination_value.h"

namespace nhl::lottery
{
    class combination
    {
    public:
        using balls_type = std::array<nhl::lottery::ball,
            nhl::lottery::balls_to_draw>;
        using iterator = typename balls_type::iterator;
        using const_iterator = typename balls_type::const_iterator;
        using reverse_iterator = typename balls_type::reverse_iterator;
        using const_reverse_iterator =
            typename balls_type::const_reverse_iterator;
        using reference = typename balls_type::reference;
        using const_reference = typename balls_type::const_reference;
        using size_type = typename balls_type::size_type;

        explicit constexpr combination(balls_type const& balls) :
            balls_{ balls }
        {
            std::ranges::sort(balls_);
        }

        // NOTE: This class is read-only once constructed

        constexpr const_reference operator[](size_type pos) const noexcept
        {
            return balls_[pos];
        }

        constexpr const_iterator begin() const noexcept
        {
            return balls_.begin();
        }

        constexpr const_iterator cbegin() const noexcept
        {
            return balls_.cbegin();
        }

        constexpr const_iterator end() const noexcept
        {
            return balls_.end();
        }

        constexpr const_iterator cend() const noexcept
        {
            return balls_.cend();
        }

        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return balls_.rbegin();
        }

        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return balls_.crbegin();
        }

        constexpr const_reverse_iterator rend() const noexcept
        {
            return balls_.rend();
        }

        constexpr const_reverse_iterator crend() const noexcept
        {
            return balls_.crend();
        }

    private:
        balls_type balls_{};
    };

    inline constexpr nhl::lottery::combination_value to_value(
        combination const& c)
    {
        return nhl::lottery::combination_value
        (
            static_cast<int>(c[0]),
            static_cast<int>(c[1]),
            static_cast<int>(c[2]),
            static_cast<int>(c[3])
        );
    }

    inline std::ostream& operator<<(std::ostream& os, combination const& c)
    {
        using std::cout;

        for (auto& ball : c)
        {
            cout << ball << " ";
        }

        return os;
    }
}

template <>
struct fmt::formatter<nhl::lottery::combination> :
    fmt::formatter<nhl::lottery::combination_value>
{
    auto format(nhl::lottery::combination const& c, fmt::format_context& ctx)
    {
        return formatter<nhl::lottery::combination_value>::format(
            to_value(c), ctx);
    }
};
