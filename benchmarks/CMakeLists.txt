
find_package(benchmark CONFIG REQUIRED)

add_executable(benchmarker

    math_benchmark.cpp

)

target_link_libraries(benchmarker
    PRIVATE
        nhl::nhl
        benchmark::benchmark
        benchmark::benchmark_main
)
