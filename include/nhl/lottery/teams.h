#pragma once

#include <array>
#include <span>
#include "nhl/lottery/lottery.h"
#include "nhl/lottery/team.h"

namespace nhl::lottery
{
    class lottery_teams
    {
    public:
        using teams_type = std::array<nhl::lottery::team,
            nhl::lottery::team_count>;
        using iterator = typename teams_type::iterator;
        using const_iterator = typename teams_type::const_iterator;
        using reverse_iterator = typename teams_type::reverse_iterator;
        using const_reverse_iterator =
            typename teams_type::const_reverse_iterator;
        using reference = typename teams_type::reference;
        using const_reference = typename teams_type::const_reference;
        using size_type = typename teams_type::size_type;

        constexpr explicit lottery_teams(teams_type const& teams) :
            teams_(teams)
        {
            std::ranges::sort(teams_, {}, &nhl::lottery::team::team_id);
        }

        // NOTE: This class is read-only once constructed

        constexpr const_reference operator[](size_type pos) const noexcept
        {
            return teams_[pos];
        }

        constexpr const_iterator begin() const noexcept
        {
            return teams_.begin();
        }

        constexpr const_iterator cbegin() const noexcept
        {
            return teams_.cbegin();
        }

        constexpr const_iterator end() const noexcept
        {
            return teams_.end();
        }

        constexpr const_iterator cend() const noexcept
        {
            return teams_.cend();
        }

        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return teams_.rbegin();
        }

        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return teams_.crbegin();
        }

        constexpr const_reverse_iterator rend() const noexcept
        {
            return teams_.rend();
        }

        constexpr const_reverse_iterator crend() const noexcept
        {
            return teams_.crend();
        }

        constexpr std::optional<nhl::team_id> lookup(int ranking) const
        {
            if (auto pos = std::ranges::find(teams_, ranking,
                &nhl::lottery::team::ranking); pos != std::ranges::end(teams_))
            {
                return pos->team_id;
            }
            return std::nullopt;
        }

    private:
        teams_type teams_;
    };
}
