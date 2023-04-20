#include <doctest/doctest.h>
#include "nhl/lottery/ranking_combinations.h"

#include "nhl/lottery/ranking.h"

TEST_CASE("combinations_per_ranking")
{
    using nhl::lottery::combinations_per_ranking;
    using nhl::lottery::ranking_combinations;

    static_assert(combinations_per_ranking.size() == 16);

    static_assert(combinations_per_ranking[0].ranking == 1);
    static_assert(combinations_per_ranking[0].combinations == 185);

    static_assert(combinations_per_ranking[1].ranking == 2);
    static_assert(combinations_per_ranking[1].combinations == 135);

    static_assert(combinations_per_ranking[2].ranking == 3);
    static_assert(combinations_per_ranking[2].combinations == 115);

    static_assert(combinations_per_ranking[3].ranking == 4);
    static_assert(combinations_per_ranking[3].combinations == 95);

    static_assert(combinations_per_ranking[4].ranking == 5);
    static_assert(combinations_per_ranking[4].combinations == 85);

    static_assert(combinations_per_ranking[5].ranking == 6);
    static_assert(combinations_per_ranking[5].combinations == 75);

    static_assert(combinations_per_ranking[6].ranking == 7);
    static_assert(combinations_per_ranking[6].combinations == 65);

    static_assert(combinations_per_ranking[7].ranking == 8);
    static_assert(combinations_per_ranking[7].combinations == 60);

    static_assert(combinations_per_ranking[8].ranking == 9);
    static_assert(combinations_per_ranking[8].combinations == 50);

    static_assert(combinations_per_ranking[9].ranking == 10);
    static_assert(combinations_per_ranking[9].combinations == 35);

    static_assert(combinations_per_ranking[10].ranking == 11);
    static_assert(combinations_per_ranking[10].combinations == 30);

    static_assert(combinations_per_ranking[11].ranking == 12);
    static_assert(combinations_per_ranking[11].combinations == 25);

    static_assert(combinations_per_ranking[12].ranking == 13);
    static_assert(combinations_per_ranking[12].combinations == 20);

    static_assert(combinations_per_ranking[13].ranking == 14);
    static_assert(combinations_per_ranking[13].combinations == 15);

    static_assert(combinations_per_ranking[14].ranking == 15);
    static_assert(combinations_per_ranking[14].combinations == 5);

    static_assert(combinations_per_ranking[15].ranking == 16);
    static_assert(combinations_per_ranking[15].combinations == 5);
}

TEST_CASE("ranking_combination_distribution")
{
    using nhl::lottery::ranking_combination_distribution;

    SUBCASE("shuffle")
    {
        bool shuffle{ true };
        const auto dist = ranking_combination_distribution(shuffle);

        REQUIRE_FALSE(std::ranges::is_sorted(dist));

        for (auto const& ranking : nhl::lottery::rankings)
        {
            const auto c = std::ranges::count_if(dist, [&ranking](auto const& r)
            {
                return r == ranking;
            });

            REQUIRE(c == nhl::lottery::combinations_for_ranking(ranking));
        }
    }

    SUBCASE("non-shuffle")
    {
        bool shuffle{ false };
        const auto dist = ranking_combination_distribution(shuffle);

        REQUIRE(std::ranges::is_sorted(dist));

        for (auto const& ranking : nhl::lottery::rankings)
        {
            const auto c = std::ranges::count_if(dist, [&ranking](auto const& r)
            {
                return r == ranking;
            });

            REQUIRE(c == nhl::lottery::combinations_for_ranking(ranking));
        }
    }
}
