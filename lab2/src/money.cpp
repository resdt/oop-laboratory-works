#include "money.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <stdexcept>

namespace xyz {

using uchar = Money::uchar;

std::string Money::toString() const {
    std::string result;
    result.push_back(toChar(data_[0]));
    if (size_ == 1)
        result.push_back('0');
    else
        result.push_back(toChar(data_[1]));
    result.push_back('.');
    for (int i = 2; i < size_; i++) {
        result.push_back(toChar(data_[i]));
    }
    if (size_ < 3) {
        result.push_back('0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void Money::increaseCapacity() {
    if (capacity_ == 0)
        capacity_ = 1;
    capacity_ = capacity_ <= SIZE_MAX / 2 ? capacity_ * 2 : SIZE_MAX;
    auto buffer = new uchar[capacity_];
    memcpy(buffer, data_, size_);
    delete[] data_;
    data_ = buffer;
}

uchar Money::toValue(uchar c) {
    if (!std::isdigit(c))
        throw std::invalid_argument("Uchar is not a digit");
    return c - '0';
}

uchar Money::toChar(uchar c) noexcept {
    return c + '0';
}

Money::Money() : data_(nullptr), size_(0), capacity_(0) {}

Money::Money(const std::size_t& n, uchar c) : capacity_(n) {
    if (n == 0)
        throw std::invalid_argument("Zero size money is not allowed");
    c = toValue(c);
    if (c == 0)
        size_ = 1;
    else {
        size_ = capacity_;
    }
    data_ = new uchar[capacity_];
    std::memset(data_, c, size_);
}

Money::Money(const std::initializer_list<uchar>& list) : capacity_(list.size()), size_(0) {
    data_ = new uchar[capacity_];
    std::size_t i{capacity_};
    try {
        bool leading = true;
        for (auto& c : list) {
            auto temp = toValue(c);
            if (temp == 0 && leading)
                continue;
            leading = false;
            data_[--i] = temp;
            size_++;
        }
        if (size_ == 0) {
            size_++;
            *data_ = 0;
        }
    } catch (...) {
        delete[] data_;
        throw;
    }
}

Money::Money(std::string_view str) : size_(1), capacity_(str.size() - 1) {
    const auto strSize = str.size();
    if (strSize >= 3 && str[strSize - 3] != '.')
        throw std::invalid_argument("Can't interpret string as money");
    data_ = new uchar[capacity_];
    try {
        bool leading = true;
        for (std::string_view::size_type i = 0; i < strSize - 3; ++i) {
            auto temp = toValue(str[i]);
            if (temp == 0 && leading)
                continue;
            leading = false;
            data_[capacity_ - i - 1] = temp;
            ++size_;
        }
        auto temp = toValue(str[strSize - 2]);
        if (temp != 0 || size_ != 1) {
            data_[1] = temp;
            ++size_;
        }
        data_[0] = toValue(str[strSize - 1]);
    } catch (...) {
        delete[] data_;
        throw std::invalid_argument("Can't interpret string as money");
    }
}

Money::Money(const Money& other) : data_(new uchar[other.size_]), size_(other.size_), capacity_(other.capacity_) {
    std::memcpy(data_, other.data_, size_);
}

Money::Money(Money&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
}

void Money::swap(Money& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::size_t Money::size() const {
    return size_;
}

std::size_t Money::capacity() const {
    return capacity_;
}

Money& Money::operator=(const Money& other) & {
    Money m{other};
    swap(m);
    return *this;
}

Money& Money::operator=(Money&& other) & {
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

void Money::pushBack(uchar c) {
    if (capacity_ == size_) {
        increaseCapacity();
    }
    data_[size_++] = c;
}

Money& Money::operator+=(const Money& other) {
    uchar carry = 0;
    std::size_t maxSize = std::max(other.size_, size_);
    for (size_t i = 0; i < maxSize || carry; ++i) {
        if (i < size_ && i < other.size_) {
            data_[i] += other.data_[i] + carry;
            carry = 0;
            if (data_[i] > 9) {
                carry = 1;
                data_[i] -= 10;
            }
        } else if (i < size_) {
            data_[i] += carry;
            break;
        } else if (i < other.size_) {
            pushBack(other.data_[i] + carry);
            carry = 0;
            if (data_[i] > 9) {
                carry = 1;
                data_[i] -= 10;
            }
        } else {
            pushBack(carry);
            carry = 0;
        }
    }
    return *this;
}

Money operator+(const Money& a, const Money& b) {
    Money m{a};
    return m += b;
}

Money& Money::operator-=(const Money& other) {
    uchar carry = 0;
    std::size_t maxSize = std::max(other.size_, size_);
    for (size_t i = 0; i < maxSize || carry; ++i) {
        if (i < size_ && i < other.size_) {
            if (data_[i] >= other.data_[i] + carry) {
                data_[i] -= other.data_[i] + carry;
                carry = 0;
            } else {
                data_[i] = 10 + data_[i] - other.data_[i] - carry;
                carry = 1;
            }
        } else if (i < size_) {
            if (data_[i] >= carry) {
                data_[i] -= carry;
                if (data_[i] == 0 && carry)
                    size_--;
                carry = 0;
                break;
            }
            else {
                data_[i] = 10 + data_[i] - carry;
            }
        } else {
            throw std::invalid_argument("Difference can't be megative");
        }
    }
    if (carry)
        throw std::invalid_argument("Difference can't be megative");
    return *this;
}

Money operator-(const Money& a, const Money& b) {
    Money m{a};
    return m -= b;
}

std::ostream& operator<<(std::ostream& stream, const Money& money) {
    for (std::size_t i = money.size_; i-- > 2;)
        stream << Money::toChar(money.data_[i]);
    if (money.size_ < 3)
        stream << '0';
    stream << '.';
    if (money.size_ < 2)
        stream << '0';
    else
        stream << Money::toChar(money.data_[1]);
    stream << Money::toChar(money.data_[0]);
    return stream;
}

std::istream& operator>>(std::istream& stream, Money& money) {
    std::string str;
    stream >> str;
    money = Money(str);
    return stream;
}

Money::~Money() noexcept {
    delete[] data_;
}

bool operator<(const Money& a, const Money& b) {
    if (a.size_ != b.size_) {
        return a.size_ < b.size_;
    }
    for (auto i = a.size_; i-- > 0;) {
        if (a.data_[i] != b.data_[i])
            return a.data_[i] < b.data_[i];
    }
    return false;
}

bool operator>(const Money& a, const Money& b) {
    return b < a;
}
bool operator<=(const Money& a, const Money& b) {
    return !(b < a);
}

bool operator>=(const Money& a, const Money& b) {
    return !(b > a);
}

bool operator==(const Money& a, const Money& b) {
    if (a.size_ != b.size_) {
        return false;
    }
    for (auto i = a.size_; i-- > 0;) {
        if (a.data_[i] != b.data_[i])
            return false;
    }
    return true;
}

bool operator!=(const Money& a, const Money& b) {
    return !(a == b);
}

}  // namespace xyz
