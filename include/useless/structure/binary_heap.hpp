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
void SiftUp(RandomIt begin, RandomIt end, RandomIt it, Comp comp) {
    RandomIt l = begin + (it - begin + 1) * 2 - 1;
    RandomIt r = begin + (it - begin + 1) * 2;
    RandomIt m = ((l < end) and comp(*l, *it) ? l : it);
    if (r < end and comp(*r, *m)) {
        m = r;
    }
    if (m != it) {
        std::swap(*it, *m);
        SiftUp(begin, end, m, comp);
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
        SiftUp(begin, end, it, comp);
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

} /* namespace useless */
