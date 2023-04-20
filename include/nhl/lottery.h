#pragma once

#include <array>
#include <algorithm>
#include <iostream>
#include "nhl/math.h"

namespace nhl
{
    struct combination
    {
        std::array<int, 4> value;
    };

    struct ranking_odds
    {
        int rank;
        double odds;
    };

    // Reference:
    // https://www.sportsnet.ca/nhl/article/2023-nhl-draft-lottery-odds-to-tank-or-not-to-tank/

    inline constexpr std::array lottery_odds
    {
        ranking_odds{ 1, 18.5 },
        ranking_odds{ 2, 13.5 },
        ranking_odds{ 3, 11.5 },
        ranking_odds{ 4, 9.5 },
        ranking_odds{ 5, 8.5 },
        ranking_odds{ 6, 7.5 },
        ranking_odds{ 7, 6.5 },
        ranking_odds{ 8, 6.0 },

        ranking_odds{ 9, 5.0 },
        ranking_odds{ 10, 3.5 },
        ranking_odds{ 11, 3.0 },
        ranking_odds{ 12, 2.5 },
        ranking_odds{ 13, 2.0 },
        ranking_odds{ 14, 1.5 },
        ranking_odds{ 15, 0.5 },
        ranking_odds{ 16, 0.5 },
        // redraw
        ranking_odds{ 17, 0.1 }
    };
    static_assert(std::ranges::size(lottery_odds) == 17);
    static_assert(std::ranges::is_sorted(lottery_odds, {}, &ranking_odds::rank));

    double get_ranking_odds(int ranking)
    {
        if (auto pos = std::ranges::find(lottery_odds, ranking, &ranking_odds::rank);
            pos != std::ranges::end(lottery_odds))
            {
                return pos->odds;
            }

        return 0;
    }

    template <std::size_t N, std::size_t S>
    constexpr std::array<combination, combination_count<N,S>()> comb()
    {
        std::array<combination, combination_count<N,S>()> ret;

        int s = S;
        int n = N;

        std::string bitmask(S, 1);    // K leading 1's
        bitmask.resize(N, 0);           // N-K trailing 0's
    
        int c = 0;
        // print integers and permute bitmask
        do
        {
            combination combo;
            std::size_t x = 0;
            for (int i = 0; i < N; ++i) // [0..N-1] integers
            {
                if (bitmask[i])
                {
                    combo.value[x] = i + 1;
                    ++x;
                }
            }

            ret[c] = combo;
            ++c;
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

        return ret;
    }

    constexpr int pick_winner(std::size_t index)
    {
        std::size_t sum = 0;
        for (auto ranking_odds : lottery_odds)
        {
            sum += static_cast<std::size_t>(ranking_odds.odds * 10);
            if (index < sum)
            {
                return ranking_odds.rank;
            }
        }

        // redraw; 11 12 13 14 represents a redraw
        return 17;
    }

    struct sort_combination
    {
        bool operator()(const combination& lhs, const combination& rhs) const
        {
            return std::ranges::lexicographical_compare(lhs.value, rhs.value);
        }
    };

    inline constexpr std::array lottery_balls
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
    };

    std::ostream& operator<<(std::ostream& os, combination const& c)
    {
        using std::cout;

        for (auto n : c.value)
        {
            cout << n << " ";
        }

        return os;
    }
}
