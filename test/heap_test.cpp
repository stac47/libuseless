#include "useless/structure/binary_heap.hpp"

#include "doctest.h"

#include <vector>
#include <utility>
#include <algorithm>

TEST_CASE("binary heap construction") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::vector<int> expected = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    useless::MakeHeap(source.begin(), source.end(), std::greater<>());
    CHECK(source == expected);
}

TEST_CASE("binary heap object construction") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::vector<int> expected = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    const useless::BinaryHeap<int, std::greater<>> heap(source.begin(), source.end());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        CHECK(heap[i] == expected[i]);
    }
    std::size_t i = 0;
    auto expectedBegin = expected.begin();
    for (auto it = heap.begin(); it != heap.end(); ++it) {
        CHECK(*it == *(expectedBegin + i));
        ++i;
    }
}

TEST_CASE("max heap object construction") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::vector<int> expected = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    const useless::MaxHeap<int> heap(source.begin(), source.end());
    std::size_t i = 0;
    auto expectedBegin = expected.begin();
    for (const int v : heap) {
        CHECK(v == *(expectedBegin + i));
        ++i;
    }
}

TEST_CASE("max heap creation") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::vector<int> expected = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    useless::MakeHeapMax(source.begin(), source.end());
    CHECK(source == expected);
}

TEST_CASE("max heap creation from object collection") {
    using Pair = std::pair<int, int>;
    int model[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::vector<Pair> source;
    for (int i = 0; i < 10; ++i) {
        source.push_back(std::make_pair(i, model[i]));
    }
    useless::MakeHeapMax(source.begin(), source.end(),
        [](const Pair& rhs, const Pair& lhs) {return rhs.second > lhs.second;});
    std::vector<int> expectedSecond = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    for (std::size_t i =0; i < 10; ++i) {
        CHECK(source[i].second == expectedSecond[i]);
    }
}

TEST_CASE("min heap creation") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    std::vector<int> expected = {1, 2, 3, 4, 7, 9, 10, 14, 8, 16};
    useless::MakeHeapMin(source.begin(), source.end());
    CHECK(source == expected);
}
