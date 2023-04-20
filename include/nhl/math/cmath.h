#pragma once

#include <concepts>
#include <cmath>
#include <stdexcept>
#include <algorithm>

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

    // supports n = 0 to 20
    inline constexpr std::size_t factorial(std::size_t n)
    {
        if (n > 20)
        {
            throw std::out_of_range("n must be between 0 and 20");
        }

        std::size_t ret{ 1 };
        for (int i = 2; i <= n; ++i)
        {
            ret *= i;
        }

        return ret;
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

        } while (std::ranges::prev_permutation(mask).found);

    }
}
