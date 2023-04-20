#include <doctest/doctest.h>
#include "nhl/lottery/ranking.h"

TEST_CASE("rankings")
{
    using nhl::lottery::rankings;

    static_assert(rankings.size() == 16);
    static_assert(rankings[0] == 1);
    static_assert(rankings[1] == 2);
    static_assert(rankings[2] == 3);
    static_assert(rankings[3] == 4);
    static_assert(rankings[4] == 5);
    static_assert(rankings[5] == 6);
    static_assert(rankings[6] == 7);
    static_assert(rankings[7] == 8);
    static_assert(rankings[8] == 9);
    static_assert(rankings[9] == 10);
    static_assert(rankings[10] == 11);
    static_assert(rankings[11] == 12);
    static_assert(rankings[12] == 13);
    static_assert(rankings[13] == 14);
    static_assert(rankings[14] == 15);
    static_assert(rankings[15] == 16);
}
