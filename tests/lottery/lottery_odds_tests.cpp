#include <doctest/doctest.h>
#include "nhl/lottery/odds.h"

TEST_CASE("ranking_first_round_odds")
{
    using nhl::lottery::first_round_odds;
    using namespace math::literals;

    static_assert(first_round_odds.size() == 16);

    static_assert(first_round_odds[0].ranking == 1);
    static_assert(first_round_odds[0].odds == 18.5_pct);

    static_assert(first_round_odds[1].ranking == 2);
    static_assert(first_round_odds[1].odds == 13.5_pct);

    static_assert(first_round_odds[2].ranking == 3);
    static_assert(first_round_odds[2].odds == 11.5_pct);

    static_assert(first_round_odds[3].ranking == 4);
    static_assert(first_round_odds[3].odds == 9.5_pct);

    static_assert(first_round_odds[4].ranking == 5);
    static_assert(first_round_odds[4].odds == 8.5_pct);

    static_assert(first_round_odds[5].ranking == 6);
    static_assert(first_round_odds[5].odds == 7.5_pct);

    static_assert(first_round_odds[6].ranking == 7);
    static_assert(first_round_odds[6].odds == 6.5_pct);

    static_assert(first_round_odds[7].ranking == 8);
    static_assert(first_round_odds[7].odds == 6_pct);

    static_assert(first_round_odds[8].ranking == 9);
    static_assert(first_round_odds[8].odds == 5_pct);

    static_assert(first_round_odds[9].ranking == 10);
    static_assert(first_round_odds[9].odds == 3.5_pct);

    static_assert(first_round_odds[10].ranking == 11);
    static_assert(first_round_odds[10].odds == 3_pct);

    static_assert(first_round_odds[11].ranking == 12);
    static_assert(first_round_odds[11].odds == 2.5_pct);

    static_assert(first_round_odds[12].ranking == 13);
    static_assert(first_round_odds[12].odds == 2_pct);

    static_assert(first_round_odds[13].ranking == 14);
    static_assert(first_round_odds[13].odds == 1.5_pct);

    static_assert(first_round_odds[14].ranking == 15);
    static_assert(first_round_odds[14].odds == .5_pct);

    static_assert(first_round_odds[15].ranking == 16);
    static_assert(first_round_odds[15].odds == .5_pct);
}
