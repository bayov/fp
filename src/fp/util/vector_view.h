#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>

namespace fp::util {

/**
 * A vector_view refers to a contiguous sequence of objects of type `T`.
 *
 * This is used instead of std::span because at the time of writing, std::span
 * is not yet available in gcc (version 9.1).
 */
template <class T>
struct vector_view {
    using value_type = std::remove_const_t<T>;
    using pointer    = const T*;
    using iterator   = pointer;

    constexpr vector_view() : data_(nullptr), size_(0) {}

    constexpr vector_view(pointer first, size_t size) :
        data_(first), size_(size) {}

    constexpr vector_view(pointer first, pointer last) :
        data_(first), size_(last - first) {}

    constexpr vector_view(const std::vector<T>& v) :
        data_(v.data()), size_(v.size()) {}

    constexpr vector_view(const std::vector<T>& v, size_t size) :
        data_(v.data()), size_(size) {}

    constexpr size_t size() const { return size_; }
    constexpr bool empty() const { return size_ == 0; }

    constexpr const T& front() const { return *data_; }
    constexpr const T&  back() const { return *(data_ + size_ - 1); }

    constexpr iterator begin() const { return data_; }
    constexpr iterator   end() const { return data_ + size_; }

    constexpr pointer data() const { return data_; }

private:
    pointer data_;
    size_t  size_;
};

} // namespace fp::util
