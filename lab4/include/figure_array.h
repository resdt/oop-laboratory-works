#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <memory>
#include <stdexcept>

template <class T>
class Array {
   public:
    Array() noexcept;
    Array(std::size_t size);
    Array(std::initializer_list<T> list);
    std::size_t capacity() const noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    void popBack();
    void pushBack(T const &fig);
    void resize(std::size_t newSize, T &value);
    void reserve(std::size_t newCapacity);
    T &operator[](std::size_t ind);
    T const &operator[](std::size_t ind) const;
    void erase(std::size_t ind);
    std::size_t size() const noexcept;
    void swap(Array &other) noexcept;
    double sumOfSquares() const noexcept;

   private:
    std::unique_ptr<T[]> data_;
    std::size_t capacity_, size_;
    std::size_t newCapacity() const;
    void reallocate(size_t newSize);
};

template <class T>
std::size_t Array<T>::capacity() const noexcept {
    return capacity_;
}

template <class T>
void Array<T>::clear() noexcept {
    size_ = 0;
}

template <class T>
bool Array<T>::empty() const noexcept {
    return size_ == 0;
}

template <class T>
void Array<T>::pushBack(T const &value) {
    if (capacity_ == size_) {
        const size_t capacity = newCapacity();
        reallocate(capacity);
        capacity_ = capacity;
    }
    data_[size_++] = value;
}

template <class T>
void Array<T>::popBack() {
    if (size_ == 0) throw std::length_error("Out of range");
    --size_;
}

template <class T>
void Array<T>::resize(const size_t newSize, T &value) {
    if (newSize <= size_) {
        size_ = newSize;
        return;
    }
    if (newSize <= capacity_) {
        while (size_ < newSize) data_[size_++] = value;
        return;
    }
    reallocate(newSize);
    capacity_ = newSize;
    while (size_ < newSize) data_[size_++] = value;
}

template <class T>
T &Array<T>::operator[](size_t ind) {
    if (size_ <= ind) {
        throw std::out_of_range("Out of range");
    }
    return data_[ind];
}

template <class T>
T const &Array<T>::operator[](std::size_t ind) const {
    if (size_ <= ind) {
        throw std::out_of_range("Out of range");
    }
    return data_[ind];
}

template <class T>
std::size_t Array<T>::size() const noexcept {
    return size_;
}

template <class T>
std::size_t Array<T>::newCapacity() const {
    if (capacity_ == 0) return 1;
    return capacity_ <= SIZE_MAX / 2 ? capacity_ * 2 : SIZE_MAX;
}

template <class T>
void Array<T>::reallocate(size_t newSize) {
    auto newData = std::make_unique<T[]>(newSize);
    std::copy(data_.get(), data_.get()+capacity_, newData.get());
    data_ = std::move(newData);
}


template <class T>
Array<T>::Array() noexcept : data_(nullptr), capacity_(0), size_(0) {}
template <class T>
Array<T>::Array(std::size_t size)
    : size_(size), capacity_(size), data_(std::make_shared<T[]>(size)) {}
template <class T>
Array<T>::Array(std::initializer_list<T> list)
    : size_(list.size()),
      capacity_(list.size()),
      data_(std::make_unique<T[]>(list.size())) {
    std::size_t c = 0;
    for (auto f : list) {
        data_[c] = f;
        ++c;
    }
}

template <class T>
void Array<T>::erase(size_t ind) {
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

template <class T>
void Array<T>::swap(Array &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

template <class T>
void Array<T>::reserve(std::size_t newCapacity) {
    reallocate(newCapacity);
    capacity_ = newCapacity;
}

template <class T>
double Array<T>::sumOfSquares() const noexcept {
    double sum = 0;
    for (std::size_t i = 0; i < size_; ++i) {
        sum += static_cast<double>(*data_[i]);
    }
    return sum;
}
