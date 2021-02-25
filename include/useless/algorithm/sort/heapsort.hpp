#include "useless/structure/binary_heap.hpp"

#include <functional>

namespace useless {

template<typename RandomIt, typename Compare = std::greater<>>
void heapsort(RandomIt begin, RandomIt end, Compare compare = Compare()) {
    if (begin == end) {
        return;
    }
    const std::size_t size = end - begin;
    useless::MakeHeapMax(begin, end, compare);
    for (std::size_t i = size - 1; i; --i) {
        RandomIt it = begin + i;
        std::swap(*begin, *it);
        SiftUp(begin, begin + i, begin, compare);
    }
}

} /* namespace useless */
