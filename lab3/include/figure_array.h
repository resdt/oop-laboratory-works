#include <cstddef>
#include <initializer_list>

#include "figure.h"

class FigureArray {
   public:
    FigureArray() noexcept;
    FigureArray(std::size_t size);
    FigureArray(std::initializer_list<Figure*> list);
    FigureArray(const FigureArray& other);
    FigureArray(FigureArray&& other) noexcept;
    std::size_t capacity() const noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    void popBack();
    void pushBack(Figure* const& fig);
    void resize(std::size_t newSize, Figure*& value);
    void reserve(std::size_t newCapacity);
    FigureArray& operator=(const FigureArray& other) noexcept;
    FigureArray& operator=(FigureArray&& other) noexcept;
    Figure*& operator[](std::size_t ind);
    Figure* const& operator[](std::size_t ind) const;
    void erase(std::size_t ind);
    std::size_t size() const noexcept;
    void swap(FigureArray& other) noexcept;
    ~FigureArray() noexcept;
    double sumOfSquares() const noexcept;

   private:
    Figure** data_;
    std::size_t capacity_, size_;
    std::size_t newCapacity() const;
    static Figure** reallocate(Figure** oldData, std::size_t oldSize,
                               std::size_t newSize);
};
