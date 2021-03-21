#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <vector>
#include <optional>
#include <sstream>
#include <functional>

namespace useless {

template<typename RandomIt, typename Comp>
void Heapify(RandomIt begin, RandomIt end, RandomIt it, Comp comp) {
    RandomIt l = begin + (it - begin + 1) * 2 - 1;
    RandomIt r = begin + (it - begin + 1) * 2;
    RandomIt m = ((l < end) and comp(*l, *it) ? l : it);
    if (r < end and comp(*r, *m)) {
        m = r;
    }
    if (m != it) {
        std::swap(*it, *m);
        Heapify(begin, end, m, comp);
    }
}

template<typename RandomIt, typename Comp>
void MakeHeap(RandomIt begin, RandomIt end, Comp comp) {
    if (begin == end) {
        return;
    }
    RandomIt it = begin + (end - begin) / 2;
    do {
        --it;
        Heapify(begin, end, it, comp);
    } while (it != begin);
}

template<typename RandomIt, typename Comp = std::greater<>>
void MakeHeapMax(RandomIt begin, RandomIt end, Comp comp = Comp()) {
    MakeHeap(begin, end, comp);
}

template<typename RandomIt, typename Comp = std::less<>>
void MakeHeapMin(RandomIt begin, RandomIt end, Comp comp = Comp()) {
    MakeHeap(begin, end, comp);
}

template<typename T, typename Comp>
class BinaryHeap final {
public:
    using Storage_t = std::vector<T>;
    using Compare_t = Comp;
    using Iterator_t = typename Storage_t::iterator;
    using ConstIterator_t = typename Storage_t::const_iterator;

    BinaryHeap() = default;
    BinaryHeap(const BinaryHeap&) = default;
    BinaryHeap& operator=(const BinaryHeap&) = default;

    template<typename RandomIt>
    BinaryHeap(RandomIt begin, RandomIt end) {
        std::copy(begin, end, std::back_inserter(storage_));
        MakeHeap(std::begin(storage_), std::end(storage_), Compare_t{});
    }

    Iterator_t begin() {
        return std::begin(storage_);
    }

    ConstIterator_t begin() const {
        return std::begin(storage_);
    }

    Iterator_t end() {
        return std::end(storage_);
    }

    ConstIterator_t end() const {
        return std::end(storage_);
    }

    T const& operator[](std::size_t i) const {
        return storage_[i];
    }
private:
    Storage_t storage_;
};

template<typename T>
using MaxHeap = BinaryHeap<T, std::greater<>>;

template<typename T>
using MinHeap = BinaryHeap<T, std::less<>>;


} /* namespace useless */
