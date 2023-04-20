#pragma once

#include <array>
#include <map>
#include <optional>
#include "nhl/lottery/lottery.h"
#include "nhl/lottery/round.h"

namespace nhl::lottery
{
    class lottery_winners
    {
    public:
        void set(round_number const& rn, int team_ranking)
        {
            winners_[rn] = team_ranking;
        }

        std::optional<int> lookup(round_number const& rn) const
        {
            if (auto pos = winners_.find(rn); pos != winners_.end())
            {
                return pos->second;
            }
            return std::nullopt;
        }

        const bool is_existing_winner(int team_ranking) const
        {
            auto pos = std::ranges::find(winners_, team_ranking,
                &std::map<round_number, int>::value_type::second);
            return (pos != std::ranges::end(winners_));
        }

    private:
        std::map<round_number, int> winners_;
    };
}
