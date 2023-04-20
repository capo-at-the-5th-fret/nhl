#pragma once

#include <array>
#include <algorithm>
#include <random>
#include "nhl/lottery/lottery.h"

namespace nhl::lottery
{
    struct ranking_combinations
    {
        int ranking;
        std::size_t combinations;
    };

    inline constexpr std::array combinations_per_ranking
    {
        ranking_combinations{ 1, 185 },
        ranking_combinations{ 2, 135 },
        ranking_combinations{ 3, 115 },
        ranking_combinations{ 4, 95 },
        ranking_combinations{ 5, 85 },
        ranking_combinations{ 6, 75 },
        ranking_combinations{ 7, 65 },
        ranking_combinations{ 8, 60 },
        ranking_combinations{ 9, 50 },
        ranking_combinations{ 10, 35 },
        ranking_combinations{ 11, 30 },
        ranking_combinations{ 12, 25 },
        ranking_combinations{ 13, 20 },
        ranking_combinations{ 14, 15 },
        ranking_combinations{ 15, 5 },
        ranking_combinations{ 16, 5 }
    };
    static_assert(combinations_per_ranking.size() == rankings_count);
    static_assert(std::ranges::is_sorted(combinations_per_ranking, {},
        &ranking_combinations::ranking));
    static_assert(std::ranges::adjacent_find(combinations_per_ranking, {},
        &ranking_combinations::ranking) == std::ranges::end(combinations_per_ranking));
    static_assert
    (
        []<std::size_t... I>(std::index_sequence<I...>)
        {
            return (... + combinations_per_ranking[I].combinations);
        }(std::make_index_sequence<rankings_count>{}) == combinations_used_count
    );

    inline constexpr std::size_t combinations_for_ranking(int ranking)
    {
        auto pos = std::ranges::find(combinations_per_ranking, ranking,
            &ranking_combinations::ranking);
        return (pos != std::ranges::end(combinations_per_ranking)) ?
            pos->combinations : 0;
    }

    inline constexpr std::array<int, combinations_used_count>
        ranking_combination_distribution(bool shuffle = true)
    {
        std::array<int, combinations_used_count> ret;

        // A ranking will be added to the return array for each possible
        // combination for that ranking
        // i.e.
        // - if N were 100 and ranking 1 had 15% odds, then 1 would appear in
        //   the return array 15 times
        // - if N were 100 and ranking 2 had 12% odds, then 2 would appear in
        //   the return array 12 times
        // etc.
        
        std::size_t ret_index{ 0 };
        for (auto const& [ranking, combinations] : combinations_per_ranking)
        {
            for (std::size_t n = 0; n < combinations; ++n)
            {
                ret[ret_index++] = ranking;
            }
        }

        static std::random_device rd;
        static std::mt19937 gen{ rd() };

        if (shuffle)
        {
            std::ranges::shuffle(ret, gen);
        }

        return ret;
    }
}
