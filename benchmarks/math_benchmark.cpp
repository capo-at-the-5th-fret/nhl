#include <benchmark/benchmark.h>

#include <array>
#include "nhl/math/cmath.h"

static void BM_for_each_combination(benchmark::State& state)
{
  std::array set = { 1, 2, 3, 4 };
  // Perform setup here
  for (auto _ : state)
  {
      int i{ 1 };
      math::for_each_combination<3,1>([&set,&i](auto const& combo)
      {
          //std::cout << std::setw(3) << i << ": ";

          for (auto const& x : combo)
          {
              //std::cout << set[x] << " ";
          }
          //std::cout << "\n";
          ++i;
      });
  }
}
// Register the function as a benchmark
BENCHMARK(BM_for_each_combination);

