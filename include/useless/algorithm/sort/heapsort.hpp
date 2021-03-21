#include "useless/structure/binary_heap.hpp"

#include <algorithm>
#include <functional>

namespace useless {

template<typename RandomIt, typename Compare = std::less<>>
void heapsort(RandomIt begin, RandomIt end, Compare compare = Compare()) {
    if (begin == end) {
        return;
    }
    const std::size_t size = end - begin;
    useless::MakeHeap(begin, end, compare);
    for (std::size_t i = size - 1; i; --i) {
        RandomIt it = begin + i;
        std::swap(*begin, *it);
        Heapify(begin, begin + i, begin, compare);
    }
    std::reverse(begin, end);
}

} /* namespace useless */
