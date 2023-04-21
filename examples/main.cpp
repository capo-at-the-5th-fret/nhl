#include <string>
#include <string_view>
#include <optional>
#include <thread>
#include <chrono>
#include <unordered_set>
#include <cxxopts.hpp>
#include <nhl/print.h>
#include <nhl/lottery/odds.h>
#include <nhl/lottery/lottery.h>
#include <nhl/lottery/machine.h>
#include <nhl/lottery/combination.h>
#include <nhl/lottery/ranking.h>
#include <nhl/lottery/stats.h>
#include <nhl/lottery/team.h>
#include <nhl/lottery/teams.h>
#include <nhl/lottery/print.h>
#include <nhl/lottery/combination_table.h>
#include <nhl/team.h>

inline constexpr std::string_view app_name{ "nhl_dls" };
inline constexpr std::string_view app_version{ "1.0" };

struct app_options
{
    std::optional<std::size_t> simulations;
    std::optional<std::size_t> rounds;

    static constexpr std::size_t min_simulations() { return 1; }

    template <std::integral T>
    static constexpr bool is_valid_simulations(T simulations)
    {
        return std::cmp_less_equal(min_simulations(), simulations);
    }

    static constexpr std::size_t min_rounds() { return 1; }
    static constexpr std::size_t max_rounds() { return 3; }

    template <std::integral T>
    static constexpr bool is_valid_rounds(T rounds)
    {
        return std::cmp_less_equal(min_rounds(), rounds) &&
            std::cmp_less_equal(rounds, max_rounds());
    }

    static constexpr std::size_t default_simulations{ 1 };
    static constexpr std::size_t default_rounds{ 2 };
};

int main(int argc, char* argv[])
{
    app_options options;

    cxxopts::Options cli_options(std::string{ app_name });
    cli_options.custom_help("[options]");

    try
    {
        cli_options.add_options()
            ("s,simulations", "The number of simulations to run",
                cxxopts::value<std::size_t>())
            ("r,rounds", "The number of lottery rounds per simulation",
                cxxopts::value<std::size_t>())
            ("v,version", "Print the version number and exit")
            ("h,help", "Print the usage information and exit")
        ;

        auto result = cli_options.parse(argc, argv);

        if (result.count("help"))
        {
            temp::println("{}", cli_options.help());
            std::exit(0);
        }
        else if (result.count("version"))
        {
            temp::println("{} version {}", app_name, app_version);
            std::exit(0);
        }

        if (result.count("simulations"))
        {
            if (auto s = result["simulations"].as<std::size_t>();
                app_options::is_valid_simulations(s))
            {
                options.simulations = s;
            }
            else
            {
                throw std::out_of_range("Invalid value for simulations");
            }
        }

        if (result.count("rounds"))
        {
            if (auto r = result["rounds"].as<std::size_t>();
                app_options::is_valid_rounds(r))
            {
                options.rounds = r;
            }
            else
            {
                throw std::out_of_range("Invalid value for rounds");
            }
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Command line error: " << e.what() << "\n";
        std::cout << cli_options.help() << "\n";
        std::exit(1);
    }

    // if at least one cli arg was used, set the defaults so it can run without
    // user interaction
    if (options.simulations && !options.rounds)
    {
        options.rounds = app_options::default_rounds;
    }
    else if (options.rounds && !options.simulations)
    {
        options.simulations = app_options::default_simulations;
    }

    while (!options.simulations)
    {
        std::string input;
        temp::println("Enter the number of simulations to run (>= {}; default = {})",
            app_options::min_simulations(), app_options::default_simulations);
        temp::println("- or -");
        temp::println("'q' to quit");

        std::getline(std::cin, input);

        if (input == "q")
        {
            return 0;
        }
        else if (input.empty())
        {
            options.simulations = app_options::default_simulations;
        }
        else
        {
            try
            {
                if (const auto s = std::stoll(input);
                    app_options::is_valid_simulations(s))
                {
                    options.simulations = static_cast<std::size_t>(s);
                }
            }
            catch (std::exception const&)
            {
            }
        }
    }

    while (!options.rounds)
    {
        std::string input;
        temp::println("Enter the number of lottery rounds (>= {} and <= {}; default = {})",
            app_options::min_rounds(), app_options::max_rounds(),
            app_options::default_rounds);
        temp::println("- or -");
        temp::println("'q' to quit");

        std::getline(std::cin, input);

        if (input == "q")
        {
            return 0;
        }
        else if (input.empty())
        {
            options.rounds = app_options::default_rounds;
        }
        else
        {
            try
            {
                if (const auto r = std::stoll(input);
                    app_options::is_valid_rounds(r))
                {
                    options.rounds = static_cast<std::size_t>(r);
                }
            }
            catch (std::exception const&)
            {
            }
        }
    }

    // Change the following variables
    const bool print_progress{ false };
    const bool print_individual_drawn_balls{ true };

    nhl::lottery::lottery_stats stats
    {
        .simulations = static_cast<std::size_t>(*options.simulations),
        .rounds = static_cast<std::size_t>(*options.rounds)
    };

    stats.lottery_teams = nhl::lottery::lottery_teams
    {
        // 2023 final standings
        std::array
        {
            nhl::lottery::team{ 1, nhl::team_id::ana },
            nhl::lottery::team{ 2, nhl::team_id::cbj },
            nhl::lottery::team{ 3, nhl::team_id::chi },
            nhl::lottery::team{ 4, nhl::team_id::sjs },
            nhl::lottery::team{ 5, nhl::team_id::mtl },
            nhl::lottery::team{ 6, nhl::team_id::ari },
            nhl::lottery::team{ 7, nhl::team_id::phi },
            nhl::lottery::team{ 8, nhl::team_id::wsh },
            nhl::lottery::team{ 9, nhl::team_id::det },
            nhl::lottery::team{ 10, nhl::team_id::stl },
            nhl::lottery::team{ 11, nhl::team_id::van },
            nhl::lottery::team{ 12, nhl::team_id::ott },
            nhl::lottery::team{ 13, nhl::team_id::buf },
            nhl::lottery::team{ 14, nhl::team_id::pit },
            nhl::lottery::team{ 15, nhl::team_id::nsh },
            nhl::lottery::team{ 16, nhl::team_id::cgy }
        }
    };

    temp::println("Running simulation(s)...");
    temp::println("");

    const auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t sim = 0; sim < stats.simulations; ++sim)
    {
        if (print_progress)
        {
            temp::println("[ NHL Lottery Draft - Simulation {} of {} ]",
                sim + 1, stats.simulations);
            temp::println("");
        }

        nhl::lottery::machine machine;
        nhl::lottery::combination_table combinations;
        combinations.populate();

        auto draft_order = nhl::lottery::rankings;

        std::unordered_set<int> winners;

        for (nhl::lottery::round_number round{ 1 }; round <=
            nhl::lottery::round_number{ static_cast<int>(stats.rounds) };)
        {
            if (print_progress)
            {
                temp::println("Running the machine for round {} of {}",
                    round, stats.rounds);
            }
        
            machine.load_balls(std::span{ nhl::lottery::balls });

            std::array<nhl::lottery::ball,
                nhl::lottery::balls_to_draw> drawn_balls;

            for (std::size_t b = 0; b < nhl::lottery::balls_to_draw; ++b)
            {
                if (print_progress && print_individual_drawn_balls)
                {
                    temp::print("    drawing ball {} ", b + 1);

                    for (int k = 0; k < 10; ++k)
                    {
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(150));
                        temp::print("-");
                    }
                    temp::print("> ");
                }

                const auto ball = machine.draw_ball();
                drawn_balls[b] = ball;

                if (print_progress && print_individual_drawn_balls)
                {
                    temp::println("{}", ball);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }

            nhl::lottery::combination combo{ drawn_balls };

            if (const auto winner = combinations.lookup(to_value(combo)))
            {
                if (print_progress)
                {
                    temp::println("The combination {} belongs to team {}.",
                        combo, *winner);
                }

                auto remaining_draft_order = draft_order | std::views::drop(
                    static_cast<int>(round) - 1);

                if (winners.contains(*winner))
                {
                    stats.redraws[round]++;

                    if (print_progress)
                    {
                        temp::println("{} is a previous winner. Redraw required",
                            *winner);
                    }
                }
                else if (auto pos = std::ranges::find(remaining_draft_order,
                    winner); pos != std::ranges::end(remaining_draft_order))
                {
                    const auto top_ranking = static_cast<int>(round);

                    const auto adjusted_ranking =
                        (winner <= nhl::lottery::max_ranking_jump) ?
                        top_ranking :
                        std::max(*winner - nhl::lottery::max_ranking_jump,
                            top_ranking);

                    const auto places_from_top = adjusted_ranking - top_ranking;

                    // Reference:
                    // https://stackoverflow.com/questions/26176001/c-easiest-most-efficient-way-to-move-a-single-element-to-a-new-position-within

                    std::ranges::rotate(
                        remaining_draft_order.begin() + places_from_top,
                        pos,
                        pos + 1
                    );

                    winners.insert(*winner);
                    stats.round_winner_stats[round][*winner]++;

                    ++round;
                }
                else
                {
                    stats.redraws[round]++;

                    if (print_progress)
                    {
                        temp::println("{} is locked in from a previous round. "
                            "Redraw required", *winner);
                    }
                }

                if (print_progress)
                {
                    temp::println("");
                }
            }
            else
            {
                stats.redraws[round]++;

                if (print_progress)
                {
                    temp::println("The combination {} requires a redraw.",
                        combo);
                }
            }

            if (print_progress)
            {
                temp::println("");
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }

        for (int ranking = 1; auto team : draft_order)
        {
            stats.draft_order_stats[ranking][team]++;
            ++ranking;
        }

        if (std::ranges::is_sorted(draft_order))
        {
            stats.original_draft_order_retained++;
        }

        if (print_progress)
        {
            nhl::lottery::print_draft_order(draft_order);
        }
    }

    const auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    temp::println("The simulation(s) took {} seconds to complete", diff.count());
    temp::println("");

    nhl::lottery::print_round_winner_stats(stats);
    nhl::lottery::print_draft_order_lottery_stats(stats);
}
