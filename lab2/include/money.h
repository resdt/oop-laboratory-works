#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

namespace xyz {

class Money {
    friend bool operator==(const Money& a, const Money& b);
    friend bool operator<(const Money& a, const Money& b);
    friend std::ostream& operator<<(std::ostream& stream, const Money& money);
    friend std::istream& operator>>(std::istream& stream, Money& money);

   public:
    using uchar = unsigned char;
    Money();
    Money(const std::size_t& n, uchar c);
    Money(const std::initializer_list<uchar>& list);
    Money(std::string_view str);
    Money(const Money& other);
    Money(Money&& other) noexcept;
    virtual ~Money() noexcept;
    void swap(Money& other) noexcept;
    Money& operator=(const Money& other) &;
    Money& operator=(Money&& other) &;
    std::size_t size() const;
    std::size_t capacity() const;
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);
    std::string toString() const;

   private:
    uchar* data_;
    std::size_t size_, capacity_;
    static uchar toChar(uchar c) noexcept;
    static uchar toValue(uchar c);
    void pushBack(uchar c);
    void increaseCapacity();
};

bool operator!=(const Money& a, const Money& b);
bool operator<=(const Money& a, const Money& b);
bool operator>(const Money& a, const Money& b);
bool operator>=(const Money& a, const Money& b);
Money operator+(const Money& a, const Money& b);
Money operator-(const Money& a, const Money& b);

}  // namespace xyz