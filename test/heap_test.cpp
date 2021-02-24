#include "useless/structure/Heap.hpp"
#include "doctest.h"

#include <vector>

TEST_CASE("binary heap construction from array") {
    int expected[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    useless::BinaryHeap<int> h(expected);
    CHECK(h.storageSize() == 10);
    CHECK(h.heapSize() == 10);
    CHECK(not h.empty());
}

TEST_CASE("binary heap construction from pointers to array") {
    int expected[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    useless::BinaryHeap<int> h(expected, expected + 10);
    CHECK(h.storageSize() == 10);
    CHECK(h.heapSize() == 10);
    CHECK(not h.empty());
}

TEST_CASE("binary heap construction") {
    std::vector<int> source = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    useless::BinaryHeap<int> h(source.cbegin(), source.cend());
    CHECK(not h.empty());
    CHECK(h.storageSize() == 10);
    CHECK(h.heapSize() == 10);
    CHECK(h.data() == source);
}

TEST_CASE("binary heap node access") {
    int expected[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    useless::BinaryHeap<int> h(expected);
    CHECK(h.parent(0).has_value());
    CHECK(h.parent(0));
    CHECK(h.parent(0).value() == 4);
    CHECK(h.parent(0) == 4);
    CHECK(h.left(0));
    CHECK(h.left(0) == 1);
    CHECK(h.right(0));
    CHECK(h.right(0) == 3);
    // We can show that in a binary heap, the leaves are at indexes:
    // (size / 2) + 1, (size / 2) + 2, ..., size -1
    for (std::size_t i = h.heapSize() / 2; i < h.heapSize(); ++i) {
        CHECK(not h.left(i));
        CHECK(not h.right(i));
    }
}

TEST_CASE("max heap creation") {
    int source[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    useless::MaxHeap h(source);
    std::vector<int> expected = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    for (std::size_t i = 0; i < expected.size(); ++i) {
        CHECK(h.node(i).value() == expected[i]);
    }
}

    /* useless::BinaryHeap<int> h; */
    /* CHECK(h.size() == 0); */
    /* CHECK(h.empty()); */
    /* h.root(4); */
    /* CHECK(h.insertLeft(0, 1) == 1); */
    /* CHECK(h.insertRight(0, 3) == 2); */
    /* //           4(0) */
    /* //          /    \ */
    /* //        1(1)   3(2) */
    /* CHECK(h.size() == 3); */
    /* CHECK(h.insertLeft(h.insertLeft(1, 2), 14) == 7); */
    /* //           4(0) */
    /* //          /    \ */
    /* //        1(1)   3(2) */
    /* //        / */
    /* //      2(3) */
    /* //      / */
    /* //    14(7) */
    /* CHECK(h.insertRight(1, 16) == 4); */
    /* CHECK(h.insertRight(3, 8) == 8); */
    /* CHECK(h.insertLeft(4, 7) == 9); */
    /* CHECK(h.insertLeft(2, 9) == 5); */
    /* CHECK(h.insertRight(2, 10) == 6); */
    /* //             4(0) */
    /* //            /    \ */
    /* //           /      \ */
    /* //          /        \ */
    /* //        1(1)       3(2) */
    /* //        /  \       /  \ */
    /* //      2(3) 16(4) 9(5) 10(6) */
    /* //      /    /   \ */
    /* //    14(7) 8(8) 7(9) */
    /* int expected[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7}; */
    /* useless::BinaryHeap expectedHeap(expected); */
    /* CHECK(h.data() == expectedHeap.data()); */

/* } */
