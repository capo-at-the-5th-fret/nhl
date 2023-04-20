#include <doctest/doctest.h>
#include "nhl/lottery/combination_value.h"

TEST_CASE("combination_value")
{
    using nhl::lottery::combination_value;

    combination_value cv{ 11, 12, 13, 14 };
    REQUIRE(cv.one() == 11);
    REQUIRE(cv.two() == 12);
    REQUIRE(cv.three() == 13);
    REQUIRE(cv.four() == 14);
}

