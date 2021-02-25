#include "useless/algorithm/sort.hpp"

#include "doctest.h"

TEST_CASE("heapsort values") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    const std::vector<int> expected = {1, 2, 3, 4, 7, 8, 9, 10, 14, 16};
    useless::heapsort(source.begin(), source.end());
    CHECK(source == expected);
}
