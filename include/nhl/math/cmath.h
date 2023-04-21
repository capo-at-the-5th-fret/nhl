#pragma once

#include <concepts>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <array>

namespace math
{
    // Reference:
    // https://stackoverflow.com/questions/1489830/efficient-way-to-determine-number-of-digits-in-an-integer
    template <std::integral T>
    constexpr std::size_t number_of_digits(T t)
    {
        return (t != 0) ?
            (static_cast<std::size_t>(std::log10(std::abs(static_cast<double>(t)))) + 1) : 1;
    }

    namespace detail
    {
        // Largest number supported by std::uint64_t is !20
        // This table contains factorial 0 through 20
        inline constexpr std::array factorials =
        {
            std::uint64_t{ 1ull },
            std::uint64_t{ 1ull },
            std::uint64_t{ 2ull },
            std::uint64_t{ 6ull },
            std::uint64_t{ 24ull },
            std::uint64_t{ 120ull },
            std::uint64_t{ 720ull },
            std::uint64_t{ 5040ull },
            std::uint64_t{ 40320ull },
            std::uint64_t{ 362880ull },
            std::uint64_t{ 3628800ull },
            std::uint64_t{ 39916800ull },
            std::uint64_t{ 479001600ull },
            std::uint64_t{ 6227020800ull },
            std::uint64_t{ 87178291200ull },
            std::uint64_t{ 1307674368000ull },
            std::uint64_t{ 20922789888000ull },
            std::uint64_t{ 355687428096000ull },
            std::uint64_t{ 6402373705728000ull },
            std::uint64_t{ 121645100408832000ull },
            std::uint64_t{ 2432902008176640000ull }
        };
        static_assert(factorials.size() == 21);
        static_assert(std::is_sorted(factorials.begin(), factorials.end()));
    }

    // supports n = 0 to 20
    inline constexpr std::uint64_t factorial(std::size_t n)
    {
        if (n > 20)
        {
            throw std::out_of_range("n must be between 0 and 20");
        }
        return detail::factorials[n];
    }

    // N = number of options
    // S = size of each combination
    template <std::size_t N, std::size_t S>
    requires (N > 0 && N <= 20 && S <= N)
    constexpr std::size_t combination_count()
    {
        return factorial(N) / (factorial(S) * factorial(N - S));
    }

    template <std::size_t N, std::size_t S, typename F>
    constexpr void for_each_combination(F f)
    {
        // Initialize an array of bools with the first S values set to true, the
        // remaining N-S values set to false
        std::array<bool, N> mask = []
            <std::size_t... I>(std::index_sequence<I...>) -> std::array<bool, N>
            {
                return std::array{ (I < S)... };
            }(std::make_index_sequence<N>{});

        do
        {
            std::array<std::size_t, S> combo;
            std::size_t j{ 0 };
            for (std::size_t i = 0; i < N; ++i)
            {
                if (mask[i])
                {
                    combo[j++] = i;
                }
            }

            f(combo);

        } while (std::prev_permutation(mask.begin(), mask.end()));
        //} while (std::ranges::prev_permutation(mask).found);
    }
}
