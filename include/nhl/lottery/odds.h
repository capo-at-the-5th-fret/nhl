#pragma once

#include <array>
#include <algorithm>
#include <random>
#include <span>
#include "nhl/math/percentage.h"
#include "nhl/lottery/lottery.h"

namespace nhl::lottery
{
    using namespace math::literals;

    struct ranking_odds
    {
        int ranking;
        math::percentage odds;
    };

    // Reference:
    // https://www.sportsnet.ca/nhl/article/2023-nhl-draft-lottery-odds-to-tank-or-not-to-tank/

    // Odds of winning the first round lottery
    inline constexpr std::array first_round_odds
    {
        ranking_odds{ 1, 18.5_pct },
        ranking_odds{ 2, 13.5_pct },
        ranking_odds{ 3, 11.5_pct },
        ranking_odds{ 4, 9.5_pct },
        ranking_odds{ 5, 8.5_pct },
        ranking_odds{ 6, 7.5_pct },
        ranking_odds{ 7, 6.5_pct },
        ranking_odds{ 8, 6.0_pct },

        ranking_odds{ 9, 5.0_pct },
        ranking_odds{ 10, 3.5_pct },
        ranking_odds{ 11, 3.0_pct },
        ranking_odds{ 12, 2.5_pct },
        ranking_odds{ 13, 2.0_pct },
        ranking_odds{ 14, 1.5_pct },
        ranking_odds{ 15, 0.5_pct },
        ranking_odds{ 16, 0.5_pct }
    };
    static_assert(std::ranges::size(first_round_odds) == 16);
    static_assert(std::ranges::is_sorted(first_round_odds, {}, &ranking_odds::ranking));
    static_assert(std::ranges::adjacent_find(first_round_odds, {}, &ranking_odds::ranking) ==
        std::ranges::end(first_round_odds));

    /*static_assert(
        []<std::size_t... I>(std::index_sequence<I...>)
        {
            return ((nhl::math::percentage{ combinations_per_ranking[I].combinations,
                nhl::lottery::combinations_used_count }
                == odds[I].odds) && ...);
        }(std::make_index_sequence<nhl::lottery::rankings_count>{})
    );*/

    inline constexpr math::percentage first_round_odds_for_ranking(int ranking)
    {
        auto pos = std::ranges::find(first_round_odds, ranking,
            &ranking_odds::ranking);
        return (pos != std::ranges::end(first_round_odds)) ? pos->odds :
            math::percentage{ 0 };
    }


}