#include <doctest/doctest.h>
#include "nhl/math/cmath.h"

#include <array>

TEST_CASE("number_of_digits")
{
    using math::number_of_digits;

    REQUIRE(number_of_digits(0) == 1);
    REQUIRE(number_of_digits(1) == 1);
    REQUIRE(number_of_digits(9) == 1);

    REQUIRE(number_of_digits(10) == 2);
    REQUIRE(number_of_digits(11) == 2);
    REQUIRE(number_of_digits(99) == 2);

    REQUIRE(number_of_digits(100) == 3);
    REQUIRE(number_of_digits(101) == 3);
    REQUIRE(number_of_digits(999) == 3);

    REQUIRE(number_of_digits(1000) == 4);
    REQUIRE(number_of_digits(1001) == 4);
    REQUIRE(number_of_digits(9999) == 4);

    REQUIRE(number_of_digits(10000) == 5);
    REQUIRE(number_of_digits(10001) == 5);
    REQUIRE(number_of_digits(99999) == 5);

    REQUIRE(number_of_digits(100000) == 6);
    REQUIRE(number_of_digits(100001) == 6);
    REQUIRE(number_of_digits(999999) == 6);

    REQUIRE(number_of_digits(1000000) == 7);
    REQUIRE(number_of_digits(1000001) == 7);
    REQUIRE(number_of_digits(9999999) == 7);
}

TEST_CASE("factorial")
{
    using math::factorial;

    constexpr std::array test_values =
    {
        std::make_pair( 0, 1ull ),
        std::make_pair( 1, 1ull ),
        std::make_pair( 2, 2ull ),
        std::make_pair( 3, 6ull ),
        std::make_pair( 4, 24ull ),
        std::make_pair( 5, 120ull ),
        std::make_pair( 6, 720ull ),
        std::make_pair( 7, 5040ull ),
        std::make_pair( 8, 40320ull ),
        std::make_pair( 9, 362880ull ),
        std::make_pair( 10, 3628800ull ),
        std::make_pair( 11, 39916800ull ),
        std::make_pair( 12, 479001600ull ),
        std::make_pair( 13, 6227020800ull ),
        std::make_pair( 14, 87178291200ull ),
        std::make_pair( 15, 1307674368000ull ),
        std::make_pair( 16, 20922789888000ull ),
        std::make_pair( 17, 355687428096000ull ),
        std::make_pair( 18, 6402373705728000ull ),
        std::make_pair( 19, 121645100408832000ull ),
        std::make_pair( 20, 2432902008176640000ull )
    };

    for (int i = 0; const auto [test_value, expected_value] : test_values)
    {
        CAPTURE(i++);
        REQUIRE(factorial(test_value) == expected_value);
    }

    REQUIRE_THROWS_AS(factorial(-1), std::out_of_range);
    REQUIRE_THROWS_AS(factorial(21), std::out_of_range);
}

TEST_CASE("combination_count")
{
    using math::combination_count;

    static_assert(combination_count<1,1>() == 1);

    static_assert(combination_count<2,1>() == 2);
    static_assert(combination_count<2,2>() == 1);

    static_assert(combination_count<4,1>() == 4);
    static_assert(combination_count<4,2>() == 6);
    static_assert(combination_count<4,3>() == 4);
    static_assert(combination_count<4,4>() == 1);

    static_assert(combination_count<8,1>() == 8);
    static_assert(combination_count<8,2>() == 28);
    static_assert(combination_count<8,3>() == 56);
    static_assert(combination_count<8,4>() == 70);
    static_assert(combination_count<8,5>() == 56);
    static_assert(combination_count<8,6>() == 28);
    static_assert(combination_count<8,7>() == 8);
    static_assert(combination_count<8,8>() == 1);
}