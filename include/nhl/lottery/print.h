#pragma once

#include <iostream>
#include "nhl/math/cmath.h"
#include "nhl/lottery/odds.h"
#include "nhl/lottery/stats.h"
#include "nhl/lottery/ranking.h"
#include "nhl/print.h"

namespace nhl::lottery
{
    inline void print_round_winner_stats(lottery_stats const& stats)
    {
        for (const auto& [round, round_stats] : stats.round_winner_stats)
        {
            const std::string_view simulation_suffix =
                (stats.simulations == 1) ? "simulation" : "simulations";

            temp::println("[ Round {} Lottery Winners ] ({} {})", round,
                stats.simulations, simulation_suffix);
            temp::println("");

            temp::println("{:^10} {:^10} {:^10}", "Team", "Wins", "Pct.");
            temp::println("{0:10} {0:10} {0:10}", "----------", "----------");

            for (auto const& ranking : rankings)
            {
                std::size_t count{ 0 };

                if (auto pos = round_stats.find(ranking);
                    pos != round_stats.end())
                {
                    count = pos->second;
                }

                temp::println("{:^10} {:^10} {:^10.3f}", ranking,
                    count,
                    math::percent(count, stats.simulations).to_ratio()
                );
            }

            std::size_t redraws{ 0 };

            if (auto pos = stats.redraws.find(round);
                pos != stats.redraws.end())
            {
                redraws = pos->second;
            }

            temp::println("{} redraws", redraws);
            temp::println("");
        }
    }

    // FIX: Pass by const&
    inline void print_draft_order_lottery_stats(lottery_stats stats)
    {
        const std::string_view simulation_suffix =
            (stats.simulations == 1) ? "simulation" : "simulations";

        temp::println("[ Draft Order Statistics ] ({} {})", stats.simulations,
            simulation_suffix);
        temp::println("");

        std::cout << "Original draft order retained: " <<
            math::percent(stats.original_draft_order_retained,
                stats.simulations) << "\n";
        temp::println("");

        // Determine the max width of a column based on the number of
        // iteratations
        const auto column_width = [&stats]() -> std::size_t
        {
            auto ret = math::number_of_digits(stats.simulations);
            if (ret > 1)
            {
                ret--;
            }

            // must be at least 2 due to ranking size (10-16 are 2 digits)
            return std::max(std::size_t{2}, ret);
        }();

        constexpr std::string_view team_column_format("{:^4}");
        constexpr std::string_view ranking_column_format("{:^5.1f}");
        constexpr std::string_view ranking_column_format_2("{:^5}");

        const std::string header_format = [&]() -> std::string
        {
            std::string ret{ team_column_format };
            ret += " ";
            for (std::size_t col = 1; col <= 16; ++col)
            {
                ret += ranking_column_format_2;

                if (col < 16)
                {
                    ret += " ";
                }
            }

            return ret;
        }();

        const auto header = std::vformat(header_format,
            std::make_format_args("Team",
            "1", "2", "3", "4", "5", "6", "7", "8",
            "9", "10", "11", "12", "13", "14", "15", "16")
        );
        std::cout << header << "\n";

        const std::string header_underline(header.size(), '-');
        std::cout << header_underline << "\n";

        const std::string row_format = [&]() -> std::string
        {
            std::string ret{ team_column_format };
            ret += " ";
            for (std::size_t col = 1; col <= 16; ++col)
            {
                ret += ranking_column_format;
                if (col < 16)
                {
                    ret += " ";
                }
            }

            return ret;
        }();

        for (auto const& ranking : rankings)
        {
            std::cout << std::vformat(team_column_format,
                std::make_format_args(ranking)) << " ";

            for (int j = 1; j <= 16; ++j)
            {
                auto const& ranking_stats = stats.draft_order_stats[j];

                int k = j;
                int v = 0;

                if (auto pos = ranking_stats.find(ranking);
                    pos != ranking_stats.end())
                {
                    v = pos->second;
                }

                if (v == 0)
                {
                    temp::print(ranking_column_format_2, "-");
                }
                else
                {
                    temp::print("{:^5.3f}", math::percent(v,
                        stats.simulations).to_ratio());
                    //std::cout << std::vformat(ranking_column_format,
                      //  std::make_format_args(v / static_cast<double>(stats.simulations) * 100.0));
                }

                if (j < 16)
                {
                    temp::print(" ");
                }
            }

            temp::println("");
        }
    }

    inline void print_draft_order(std::array<int, nhl::lottery::rankings_count>
        const& draft_order)
    {
        temp::println("[ Draft Order ]");
        temp::println("");

        temp::println("{:^3} {:^4} {:^3}", " # ", "Team", "+/-");
        temp::println("{:^3} {:^4} {:^3}", "---", "----", "---");

        for (int ranking = 1; auto team : draft_order)
        {
            const auto change = [&ranking, &team]() -> std::string
            {
                if (const int change = team - ranking; change != 0)
                {
                    return std::format("{:+}", change);
                }
                else
                {
                    return "-";
                }
            }();

            temp::println("{:^3} {:^4} {:^3}", ranking, team, change);

            ++ranking;
        }

        temp::println("");
    }
}