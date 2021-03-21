#include "useless/algorithm/sort.hpp"

#include "benchmark/benchmark.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <functional>

class FixedSizeUnorderedListFixture: public benchmark::Fixture {
public:
    void SetUp(const benchmark::State&) override {
        source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    }

    void TearDown(const benchmark::State&) override {}

    std::vector<int> source;
};

BENCHMARK_F(FixedSizeUnorderedListFixture, heapsort)(benchmark::State& state) {
    for (auto _ : state) {
        useless::heapsort(source.begin(), source.end());
    }
}

BENCHMARK_F(FixedSizeUnorderedListFixture, stdsort)(benchmark::State& state) {
    for (auto _ : state) {
        std::sort(source.begin(), source.end());
    }
}

template<typename T>
class GenericSorter final {
public:

};

static void GenericSortBenchmark(std::function<void(std::vector<int>&)> func, benchmark::State& state) {
    std::vector<int> v(state.range(0));
    std::iota(v.begin(), v.end(), 0);
    for (auto _ : state) {
        state.PauseTiming();
        std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
        state.ResumeTiming();
        func(v);
    }
}

static void BM_StdSort(benchmark::State& state) {
    GenericSortBenchmark([](std::vector<int>& v) {std::sort(v.begin(), v.end());}, state);
}
BENCHMARK(BM_StdSort)->Range(1<<5, 1<<10);

static void BM_HeapSort(benchmark::State& state) {
    GenericSortBenchmark([](std::vector<int>& v) {useless::heapsort(v.begin(), v.end());}, state);
}
BENCHMARK(BM_HeapSort)->Range(1<<5, 1<<10);
