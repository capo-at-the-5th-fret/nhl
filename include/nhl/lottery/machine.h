#pragma once

#include <span>
#include <vector>
#include <algorithm>
#include <random>
#include "nhl/lottery/ball.h"

namespace nhl::lottery
{
    class machine
    {
    public:
        machine() = default;

        template<typename T, std::size_t N>
        requires (std::is_same_v<std::remove_cvref_t<T>, ball>)
        explicit machine(std::span<T,N> balls) :
            balls_{ balls.begin(), balls.end() }
        {
        }

        template<typename T, std::size_t N>
        requires (std::is_same_v<std::remove_cvref_t<T>, ball>)
        void load_balls(std::span<T,N> balls)
        {
            balls_.assign(balls.begin(), balls.end());
        }

        ball draw_ball()
        {
            static std::random_device rd;
            static std::mt19937 gen{rd()};

            const auto balls_remaining = balls_.size();

            if (balls_remaining == 0)
            {
                throw std::runtime_error("There are no balls in the machine");
            }

            const auto index = [&]() -> std::size_t
            {
                if (balls_remaining > 1)
                {
                    std::uniform_int_distribution<std::size_t> ball_dist{ 0,
                        balls_remaining - 1 };

                    return ball_dist(gen);
                }

                return 0;
            }();

            auto ret = balls_[index];
            std::erase(balls_, ret);
            return ret;
        }

    private:
        std::vector<ball> balls_;
    };
}
