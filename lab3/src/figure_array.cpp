#include "figure_array.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#include <cstring>
#include <cstdint>
#include <stdexcept>

static size_t newCapacity(size_t capacity);

std::size_t FigureArray::capacity() const noexcept { return capacity_; }

void FigureArray::clear() noexcept { size_ = 0; }

FigureArray::~FigureArray() noexcept { delete[] data_; }

bool FigureArray::empty() const noexcept { return size_ == 0; }

void FigureArray::pushBack(Figure *const &value) {
    if (capacity_ == size_) {
        const size_t capacity = newCapacity();
        Figure **data = reallocate(data_, capacity_, capacity);
        data_ = data;
        capacity_ = capacity;
    }
    data_[size_++] = value;
}

void FigureArray::popBack() {
    if (size_ == 0) throw std::length_error("Out of range");
    --size_;
}

void FigureArray::resize(const size_t newSize, Figure *&value) {
    if (newSize <= size_) {
        size_ = newSize;
        return;
    }
    if (newSize <= capacity_) {
        while (size_ < newSize) data_[size_++] = value;
        return;
    }
    Figure **data = reallocate(data_, size_, newSize);
    data_ = data;
    capacity_ = newSize;
    while (size_ < newSize) data_[size_++] = value;
}

Figure *&FigureArray::operator[](size_t ind) {
    if (size_ <= ind) {
        throw std::out_of_range("Out of range");
    }
    return data_[ind];
}

Figure *const &FigureArray::operator[](std::size_t ind) const {
    if (size_ <= ind) {
        throw std::out_of_range("Out of range");
    }
    return data_[ind];
}

std::size_t FigureArray::size() const noexcept { return size_; }

std::size_t FigureArray::newCapacity() const {
    if (capacity_ == 0) return 1;
    return capacity_ <= SIZE_MAX / 2 ? capacity_ * 2 : SIZE_MAX;
}

Figure **FigureArray::reallocate(Figure **oldData, size_t oldSize,
                                 size_t newSize) {
    Figure **data = new Figure *[newSize];
    for (size_t i = 0; i < std::min(oldSize, newSize); i++) {
        data[i] = oldData[i];
    }
    if (oldData != nullptr) {
        delete[] oldData;
    }
    return data;
}

FigureArray::FigureArray() noexcept : data_(nullptr), capacity_(0), size_(0) {}
FigureArray::FigureArray(std::size_t size)
    : size_(size), capacity_(size), data_(reallocate(nullptr, 0, size)) {}
FigureArray::FigureArray(std::initializer_list<Figure *> list)
    : size_(list.size()),
      capacity_(list.size()),
      data_(reallocate(nullptr, 0, list.size())) {
    std::size_t c = 0;
    for (auto f : list) {
        data_[c] = f;
        ++c;
    }
}
FigureArray::FigureArray(const FigureArray &other)
    : data_(reallocate(nullptr, 0, other.size_)),
      size_(other.size_),
      capacity_(other.capacity_) {
    std::memcpy(data_, other.data_, size_ * sizeof(Figure *));
}
FigureArray::FigureArray(FigureArray &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    delete[] other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

FigureArray &FigureArray::operator=(const FigureArray &other) noexcept {
    FigureArray m{other};
    swap(m);
    return *this;
}
FigureArray &FigureArray::operator=(FigureArray &&other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    return *this;
}

void FigureArray::erase(size_t ind) {
    if (ind >= size_) {
        throw std::out_of_range("Out of range");
    }
    for (std::size_t i = ind + 1; i < size_; ++i) {
        data_[i - 1] = data_[i];
    }
    if (ind < size_) {
        --size_;
    }
}

void FigureArray::swap(FigureArray &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

void FigureArray::reserve(std::size_t newCapacity) {
    data_ = reallocate(data_, capacity_, newCapacity);
    capacity_ = newCapacity;
}

double FigureArray::sumOfSquares() const noexcept {
    double sum = 0;
    for (std::size_t i = 0; i < size_; ++i) {
        sum += static_cast<double>(*data_[i]);
    }
    return sum;
}
