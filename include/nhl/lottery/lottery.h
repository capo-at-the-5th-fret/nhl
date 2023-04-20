#pragma once

#include <cstddef>
#include <utility>

namespace nhl::lottery
{
    inline constexpr std::size_t lottery_rounds{ 2 };
    inline constexpr std::size_t balls_to_draw{ 4 };

    inline constexpr std::size_t team_count{ 16 };
    inline constexpr std::size_t rankings_count{ team_count };
    inline constexpr int max_ranking_jump{ 10 };
    static_assert(std::cmp_less(max_ranking_jump, rankings_count));

    inline constexpr std::size_t ball_count{ 14 };
    inline constexpr std::size_t combination_size{ 4 };

    // 1001 combinations, with 1 reserved for "redraw"
    inline constexpr std::size_t combination_count{ 1001 };
    inline constexpr std::size_t combinations_used_count{ 1000 };
}
