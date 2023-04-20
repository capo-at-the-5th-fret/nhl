#pragma once

#include <ranges>
#include "nhl/print.h"
#include "nhl/lottery/lottery.h"
#include "nhl/lottery/ranking_combinations.h"
#include "nhl/lottery/combination_value.h"

namespace nhl::lottery
{
    class combination_table
    {
    public:
        using combinations_type =
            std::unordered_map<combination_value, int>;

        void populate()
        {
            combinations_.clear();

            const auto dist = ranking_combination_distribution();

            std::size_t dist_index{ 0 };
            nhl::lottery::for_each_combination_value(
                [&](auto const& combo)
            {
                if (dist_index < dist.size())
                {
                    combinations_[combo] = dist[dist_index++];
                }
                // left overs are considered redraws. If there's a need for
                // something more advanced, pass a predicate into the function
                // that returns whether a combo is a redraw
                // 
                // else
                // {
                //     combinations_[combo] = 0;
                // }
            });
        }

        combinations_type const& combinations() const
        {
            return combinations_;
        }

        std::optional<int> lookup(combination_value const& combo) const
        {
            if (auto pos = combinations_.find(combo);
                pos != combinations_.end())
            {
                return pos->second;
            }

            return std::nullopt;
        }

    private:
        combinations_type combinations_;
    };

    inline void print_combination_table(combination_table const& table)
    {
        temp::println("Combination Table");
        temp::println("-----------------");

        // sort the combinations with the help of a vector + reference_wrapper

        using kv_type = std::add_const_t<
            typename combination_table::combinations_type::value_type>;

        std::vector<std::reference_wrapper<kv_type>> sorted_combinations
            ( table.combinations().begin(), table.combinations().end() );

        std::ranges::sort(sorted_combinations,
            [](auto const& lhs, auto const& rhs)
            {
                return lhs.get().first < rhs.get().first;
            });

        for (auto const& combo : sorted_combinations)
        {
            std::cout << combo.get().first << " => " << combo.get().second <<
                "\n";
        }

        temp::println("");
    }
}
