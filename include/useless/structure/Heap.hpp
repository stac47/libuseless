#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <vector>
#include <optional>
#include <sstream>

namespace useless {

template<typename T>
class BinaryHeap {
    using Storage_t = std::vector<T>;
public:
    virtual ~BinaryHeap() = default;
    BinaryHeap() = default;
    BinaryHeap(const BinaryHeap&) = default;
    BinaryHeap& operator=(const BinaryHeap&) = default;

    template<std::size_t S>
    explicit BinaryHeap(T (&array)[S]) : storage_(array, array + S), heapSize_(S)
    {}

    template<typename InputIt>
    BinaryHeap(InputIt first, InputIt last): BinaryHeap() {
        std::copy(first, last, std::back_inserter(storage_));
        heapSize_ = storage_.size();
    }

    const Storage_t& data() const {
        return storage_;
    }

    std::size_t storageSize() const {
        return storage_.size();
    }

    std::size_t heapSize() const {
        return heapSize_;
    }

    void setHeapSize(std::size_t heapSize) {
        if (heapSize > storageSize()) {
            throw std::overflow_error("Storage size lower than required heap size");
        }
        heapSize_ = heapSize;
    }

    bool empty() const {
        return storage_.empty();
    }

    std::optional<T> parent(std::size_t i) const {
        return node(parentIndex(i));
    }

    std::optional<T> left(std::size_t i) const {
        return node(leftIndex(i));
    }

    std::optional<T> right(std::size_t i) const {
        return node(rightIndex(i));
    }

    std::optional<T> node(std::size_t i) const {
        if (i < storage_.size()) {
            return std::make_optional(storage_[i]);
        }
        return std::nullopt;
    }

protected:
    void swap(std::size_t i, std::size_t j) {
        std::swap(storage_.at(i), storage_.at(j));
    }

    static std::size_t parentIndex(std::size_t i)
    {
        return i / 2;
    }

    static std::size_t leftIndex(std::size_t i)
    {
        return (i + 1) * 2 - 1;
    }

    static std::size_t rightIndex(std::size_t i)
    {
        return (i + 1) * 2;
    }

private:
    Storage_t storage_;
    std::size_t heapSize_;
};

template<typename T>
class MaxHeap final : public BinaryHeap<T> {
public:
    virtual ~MaxHeap() = default;
    MaxHeap() = default;
    MaxHeap(const MaxHeap&) = default;
    MaxHeap& operator=(const MaxHeap&) = default;

    template<typename InputIt>
    MaxHeap(InputIt start, InputIt end)
      : BinaryHeap<T>(start, end)
    {
        if (this->storageSize() == 0) {
            return;
        }
        for (std::size_t i = (this->heapSize() - 1) / 2; i ; --i)
        {
            siftUp(i);
        }
        siftUp(0);
    }

    template<std::size_t S>
    explicit MaxHeap(T (&array)[S]) : MaxHeap(array, array + S)
    {}

    void siftUp(std::size_t i)
    {
        std::size_t l = BinaryHeap<T>::leftIndex(i);
        std::size_t r = BinaryHeap<T>::rightIndex(i);
        std::size_t max = ((l < this->heapSize() and this->node(l).value() > this->node(i).value())? l : i);
        if (r < this->heapSize() and this->node(r).value() > this->node(max).value()) {
            max = r;
        }
        if (max != i) {
            this->swap(i, max);
            siftUp(max);
        }
    }
};

} /* namespace useless */
