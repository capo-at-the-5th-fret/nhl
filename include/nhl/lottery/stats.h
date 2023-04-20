#pragma once

#include <map>
#include <unordered_map>
#include "nhl/print.h"
#include "nhl/lottery/teams.h"
#include "nhl/lottery/round.h"

namespace nhl::lottery
{
    struct lottery_stats
    {
        std::size_t simulations{ 1 };
        std::size_t rounds{ 2 };
        std::optional<lottery_teams> lottery_teams;

        // round -> { ranking (winner) -> count }
        std::map<round_number, std::map<int, std::size_t>> round_winner_stats;

        std::unordered_map<int, std::size_t> first_round_winner_stats;
        std::unordered_map<int, std::size_t> second_round_winner_stats;
        std::unordered_map<int, std::unordered_map<int, std::size_t>> draft_order_stats;

        std::size_t original_draft_order_retained{ 0 };

        std::unordered_map<round_number, std::size_t> redraws;
    };
}