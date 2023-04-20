#include <string>
#include <string_view>
#include <optional>
#include <map>
#include <set>
#include <thread>
#include <chrono>
#include <unordered_map>
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

#if 0
int main()
{
    using std::cout;

    nhl::lottery_machine machine;
    machine.load_balls(std::span{ test::lottery_balls });

    constexpr int balls_to_draw{ 4 };
    std::array<nhl::ball, balls_to_draw> drawn_balls;

    for (int b = 0; b < balls_to_draw; ++b)
    {
        cout << "drawing ball " << b + 1 << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        const auto ball = machine.draw_ball();
        cout << ball << "\n";
        drawn_balls[b] = ball;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    test::nhl_lottery_combination combo{ drawn_balls };
    cout << "Result: " << combo << "\n";
}
#endif

#if 0
int main()
{
    using namespace nhl;

    using std::cout;

    std::map<int, int> stats;

    const auto combos = comb<14,4>();

    std::random_device rd;
    std::mt19937 gen{rd()};

    constexpr int lottery_rounds{ 2 };

    const int simulations = 1;
    for (int i = 0; i < simulations; ++i)
    {
        std::optional<int> first_round_winner;
        std::optional<int> second_round_winner;

        while (!second_round_winner)
        {
            cout << "Running the machine ";
            if (!first_round_winner)
            {
                cout << "for round 1..." << "\n";
            }
            else
            {
                cout << "for round 2..." << "\n";
            }

            auto result = lottery_balls;
            std::ranges::shuffle(result, gen);

            combination c
            {
                { result[0], result[1], result[2], result[3] }
            };

            for (int b = 0; b < 4; ++b)
            {
                cout << "drawing ball " << b + 1 << "...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << result[b] << "\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            std::ranges::sort(c.value);
            cout << "The combiation is: " <<
                c.value[0] << " " <<
                c.value[1] << " " <<
                c.value[2] << " " <<
                c.value[3] << "\n";

            if (auto pos = std::ranges::lower_bound(combos, c,
                sort_combination{}); pos != std::ranges::end(combos))
            {
                auto index = std::ranges::distance(std::ranges::begin(combos),
                    pos);
                auto winner = pick_winner(index);

                // 11 12 13 14
                if (winner == 17)
                {
                    cout << "This combination requires a redraw." << "\n";
                }
                else if (first_round_winner)
                {
                    if (winner == *first_round_winner)
                    {
                        cout << "This combination belongs to first round winner. "
                        "A redraw is required." << "\n";
                    }
                    else
                    {
                        second_round_winner = winner;
                        cout << "The second round winner is " << winner << "\n";
                    }
                }
                else
                {
                    first_round_winner = winner;
                    cout << "The first round winner is " << winner << "\n";
                }
                cout << "\n";
            }
        }

        std::set<int> ranks =
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
        };

        std::array<std::optional<int>, 16> draft_order = {};

        const int first_round_winner_placement = *first_round_winner -
            std::min(*first_round_winner - 1, 10);

        draft_order[first_round_winner_placement - 1] = *first_round_winner;
        ranks.erase(*first_round_winner);

        const int second_round_winner_placement = *second_round_winner -
            std::min(*second_round_winner - 1, 10);

        // slot taken by first round winner, push second rounder winner down
        // one slot
        if (draft_order[second_round_winner_placement - 1])
        {
            draft_order[second_round_winner_placement] = *second_round_winner;
        }
        else
        {
            draft_order[second_round_winner_placement - 1] =
                *second_round_winner;
        }
        ranks.erase(*second_round_winner);

        cout << "Draft Order" << "\n";
        cout << "-----------" << "\n";

        auto pos = ranks.begin();
        for (auto i = 0; i < 16; ++i)
        {
            cout << std::setw(2) << i + 1 << ": ";

            if (!draft_order[i])
            {
                draft_order[i] = *pos;
                pos++;
            }

            cout << std::setw(2) << *draft_order[i];

            const int change = *draft_order[i] - (i + 1);
            if (change > 0)
            {
                cout << " (+" << change << ")" << "\n";
            }
            else if (change < 0)
            {
                cout << " (" << change << ")" << "\n";
            }
            else
            {
                cout << " (--)" << "\n";
            }
        }
    }

#if 0
    // 17 is the redraw
    for (int i = 1; i <= 17; ++i)
    {
        int k = i;
        int v = 0;

        if (auto pos = stats.find(i); pos != stats.end())
        {
            k = pos->first;
            v = pos->second;
        }
        
        cout << k << " " << v <<
                " (" << v / static_cast<double>(simulations) * 100 << "% vs " <<
                get_ranking_odds(i) << "%)" << std::endl;
    }
#endif
}
#endif

#if 0
    class combination_value
    {
    public:
        constexpr explicit combination_value(std::uint16_t value) :
            value_(value)
        {
        }

        std::uint16_t value() const { return value_; }

    private:
        std::uint16_t value_{ 0b0001'0001'0001'0001 };
    };
#endif

#if 0
        auto pos = rankings.begin();
        for (auto i = 0; i < 16; ++i)
        {
            if (print_progress)
            {
                cout << std::setw(2) << i + 1 << ": ";
            }

            if (!draft_order[i])
            {
                draft_order[i] = *pos;
                pos++;
            }

            if (print_progress)
            {
                cout << std::setw(2) << *draft_order[i];

                const int change = *draft_order[i] - (i + 1);
                if (change > 0)
                {
                    cout << " (+" << change << ")" << "\n";
                }
                else if (change < 0)
                {
                    cout << " (" << change << ")" << "\n";
                }
                else
                {
                    cout << " (--)" << "\n";
                }
            }

            stats.draft_order_stats[i + 1][*draft_order[i]]++;
        }
#endif

#if 0
        // std::unordered_map<nhl::combination_value, int> combinations;

        // const auto dist = test::ranking_odds_distribution();

        // std::size_t dist_index{ 0 };
        // nhl::for_each_combination_value(
        //     [&combinations, &dist, &dist_index](auto const& combo)
        // {
        //     //cout << std::setw(4) << i++ << ": " << combo << "\n";
        //     if (dist_index < dist.size())
        //     {
        //         combinations[combo] = dist[dist_index++];
        //     }
        //     else
        //     {
        //         combinations[combo] = -1;
        //     }
        // });

        // for (const auto& [combo, ranking] : combinations)
        // {
        //     cout << combo << " assigned to " << ranking << "\n";
        // }
        #endif

#if 0
            if (auto pos = combinations.find(to_value(combo));
                pos != combinations.end())
            {
                const auto winner = pos->second;

                // 11 12 13 14
                if (winner == -1)
                {
                    stats.first_round_redraws++;

                    if (print_progress)
                    {
                        cout << "This combination requires a redraw." << "\n";
                    }
                }
                // first round lottery winner
                else if (!first_round_winner)
                {
                    first_round_winner = winner;
                    stats.first_round_winner_stats[winner]++;
                    if (print_progress)
                    {
                        cout << "The first round winner is " << winner << "\n";
                    }
                }
                // second round lottery
                else
                {
                    // The winner of the first round is a redraw; the 1 team is
                    // also a redraw if teams 12 to 16 won the first round
                    if ((winner == *first_round_winner) ||
                        (winner == 1 && (*first_round_winner >= 12)))
                    {
                        stats.second_round_redraws++;

                        if (print_progress)
                        {
                            cout << "This combination belongs to first round winner. "
                            "A redraw is required." << "\n";
                        }
                    }
                    else
                    {
                        second_round_winner = winner;
                        stats.second_round_winner_stats[winner]++;

                        if (print_progress)
                        {
                            cout << "The second round winner is " << winner <<
                                "\n";
                        }
                    }
                }
            }
            else
            {
                if (print_progress)
                {
                    cout << "Error: combination not found" << "\n";
                }
            }
#endif

#if 0
        std::set<int> rankings =
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
        };

        std::array<std::optional<int>, 16> draft_order = {};

        const int first_round_winner_placement = std::max(1,
            *first_round_winner - 10);

        draft_order[first_round_winner_placement - 1] = *first_round_winner;
        rankings.erase(*first_round_winner);

        // move the winner to new position
        {
            auto pos = draft_order_2.begin() +
                (first_round_winner_placement - 1);
            std::rotate(draft_order_2.begin(), pos, draft_order_2.end());
        }

        if (first_round_winner_placement > 1)
        {
            draft_order[0] = 1;
            rankings.erase(1);
        }

        const int second_round_winner_placement = std::max(2,
            *second_round_winner - 10);

        // slot taken by first round winner, push second rounder winner down
        // one slot
        if (draft_order[second_round_winner_placement - 1])
        {
            draft_order[second_round_winner_placement] = *second_round_winner;
            std::swap(draft_order[second_round_winner_placement],
                draft_order[second_round_winner_placement - 1]);
        }
        else
        {
            draft_order[second_round_winner_placement - 1] =
                *second_round_winner;
        }
        rankings.erase(*second_round_winner);
#endif

#if 0
        std::array<int, 16> draft_order =
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
        };

        {
            const auto adjusted_ranking = std::max(1, *first_round_winner - 10);
            auto pos = std::find(draft_order.rbegin(), draft_order.rend(),
                *first_round_winner);
            std::rotate(pos, pos + 1, draft_order.rend() -
                adjusted_ranking + 1);
        }

        {
            const auto adjusted_ranking = std::max(2,
                *second_round_winner - 10);
            auto pos = std::find(draft_order.rbegin(), draft_order.rend(),
                *second_round_winner);
            std::rotate(pos, pos + 1, draft_order.rend() -
                adjusted_ranking + 1);
        }
#endif

#if 0
namespace test
{
    using namespace nhl;

#if 0
    inline constexpr std::array lottery_balls
    {
        nhl::lottery::ball{ 1 },
        nhl::lottery::ball{ 2 },
        nhl::lottery::ball{ 3 },
        nhl::lottery::ball{ 4 },
        nhl::lottery::ball{ 5 },
        nhl::lottery::ball{ 6 },
        nhl::lottery::ball{ 7 },
        nhl::lottery::ball{ 8 },
        nhl::lottery::ball{ 9 },
        nhl::lottery::ball{ 10 },
        nhl::lottery::ball{ 11 },
        nhl::lottery::ball{ 12 },
        nhl::lottery::ball{ 13 },
        nhl::lottery::ball{ 14 },
    };
    static_assert(lottery_balls.size() == 14);
    static_assert(std::ranges::is_sorted(lottery_balls));
    static_assert(std::ranges::adjacent_find(lottery_balls) ==
        std::ranges::end(lottery_balls));
#endif

#if 0
    inline constexpr std::size_t factorial(std::size_t n)
    {
        std::size_t f{ 1 };
        for (std::size_t i = 1; i <= n; ++i)
        {
            f *= i;
        }
        return f;
    }

    // N = number of options
    // S = size of each combination
    template <std::size_t N, std::size_t S>
    constexpr std::size_t comb_count()
    {
        return factorial(N) / (factorial(S) * factorial(N - S));
    }

    template <std::size_t N, std::size_t S>
    constexpr std::array<nhl_lottery_combination, comb_count<N,S>()> comb()
    {
        std::array<nhl_lottery_combination, comb_count<N,S>()> ret;

        std::string bitmask(S, 1); // K leading 1's
        bitmask.resize(N, 0); // N-K trailing 0's
    
        int c = 0;
        // print integers and permute bitmask
        do
        {
            nhl_lottery_combination::data_type combo;
            std::size_t x = 0;
            for (int i = 0; i < N; ++i) // [0..N-1] integers
            {
                if (bitmask[i])
                {
                    combo[x] = ball{ i + 1 };
                    ++x;
                }
            }

            ret[c] = combo;
            ++c;
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

        return ret;
    }
#endif

#if 0
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

        std::cout << "size of mask: " << sizeof(mask) << "\n";

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

    }

    template <std::size_t N, std::size_t S>
    constexpr void comb2()
    {
        std::string bitmask(S, 1);    // S leading 1's
        bitmask.resize(N, 0);           // N-S trailing 0's

        int c = 0;
        // print integers and permute bitmask
        do
        {
            constexpr auto W = std::bit_width(N);
            std::bitset<W> bs{ 0 };

            std::size_t x = 0;
            for (std::size_t i = 0; i < N; ++i)
            {
                if (bitmask[i])
                {
                    std::cout << (i + 1);
                    //bs.set(i);
                }
            }

            //std::cout << bs << "\n";
            ++c;
        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }

    // N = total number of combinations
    template <std::size_t N = nhl::lottery::combinations_used_count>
    constexpr std::array<int, N> ranking_odds_distribution()
    {
        std::array<int, N> ret;

        // A ranking will be added to the return array for each possible
        // combination for that ranking
        // i.e.
        // - if N were 100 and ranking 1 had 15% odds, then 1 would appear in
        //   the return array 15 times
        // - if N were 100 and ranking 2 had 12% odds, then 1 would appear in
        //   the return array 12 times
        // etc.
        std::size_t ret_index{ 0 };
        for (auto const& [ranking, odds] : nhl::lottery::first_round_odds)
        {
            const std::size_t combinations_for_ranking
            {
                static_cast<std::size_t>(N / 100.0 * static_cast<double>(odds))
            };

            for (std::size_t n = 0; n < combinations_for_ranking; ++n)
            {
                ret[ret_index++] = ranking;
            }
        }

        static std::random_device rd;
        static std::mt19937 gen{rd()};
        std::ranges::shuffle(ret, gen);

        return ret;
    }
#endif
}
#endif

#if 0
int main(int argc, char* argv[])
{
    auto program = argparse::ArgumentParser
    {
        std::string{ app_name },
        std::string{ app_version }
    };

    // number of simulations
    using simulations_type = decltype(cli_arg_simulations)::type;

    program.add_argument(cli_arg_simulations.primary,
        cli_arg_simulations.secondary)
        .help(std::string{ cli_arg_simulations.help })
        .scan<cli_arg_simulations.shape, simulations_type>();

    // number of rounds
    using rounds_type = decltype(cli_arg_rounds)::type;

    program.add_argument(cli_arg_rounds.primary,
        cli_arg_rounds.secondary)
        .help(std::string{ cli_arg_rounds.help })
        .scan<cli_arg_rounds.shape, rounds_type>();

    try
    {
        program.parse_args(argc, argv);
    }
    catch (std::exception const& e)
    {
        std::cerr << "command line error: " << e.what() << "\n";
        std::cerr << program;
        std::exit(1);
    }

    auto simulations = program.present<simulations_type>(
        cli_arg_simulations.primary);
    auto rounds = program.present<rounds_type>(cli_arg_rounds.primary);

    inline constexpr std::string_view app_name{ "NHL Draft Lottery Simulator" };
inline constexpr std::string_view app_version{ "1.0" };

inline constexpr command_line_arg<'u', std::size_t, 1> cli_arg_simulations
{
    .primary = "--simulations",
    .secondary = "-s",
    .help = "the number of simulations to run"
};

inline constexpr command_line_arg<'u', std::size_t,
    nhl::lottery::lottery_rounds> cli_arg_rounds
{
    .primary = "--rounds",
    .secondary = "-r",
    .help = "the number of lottery rounds"
};

#endif

#if 0
    if (!lottery_winners.is_existing_winner(*winner))
    {
        lottery_winners.set(round, *winner);
    }
    else
    {
        stats.redraws[round]++;
    }
#endif

    /*if (!first_round_winner)
    {
        first_round_winner = *winner;
        stats.first_round_winner_stats[*winner]++;
    }
    else if (*winner == *first_round_winner)
    {
        stats.second_round_redraws++;
        if (print_progress)
        {
            temp::print(", who was the first round winner. "
                "A redraw is required");
        }
    }
    else if (*winner == 1 && (*first_round_winner >= 12))
    {
        stats.second_round_redraws++;
        if (print_progress)
        {
            temp::print(", who is locked into the first overall pick. "
                "A redraw is required");
        }
    }
    else
    {
        second_round_winner = *winner;
        stats.second_round_winner_stats[*winner]++;
    }*/
