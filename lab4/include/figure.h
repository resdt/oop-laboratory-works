#pragma once

#include <cmath>
#include <concepts>
#include <iostream>

template <class T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <Number T>
bool eq(T lhs, T rhs, double epsilon = 1e-6) {
    if constexpr (std::is_integral_v<T>)
        return lhs == rhs;
    else
        return std::abs(lhs - rhs) < epsilon;
}

template <Number T>
struct Point {
    T x, y;
    Point() : x(0), y(0){};
    Point(T x, T y) : x(x), y(y){};

    static double distance(Point const& first, Point const& second) {
        return std::sqrt((second.x - first.x) * (second.x - first.x) +
                         (second.y - first.y) * (second.y - first.y));
    }

    static T distanceSquare(Point const& first, Point const& second) {
        return (second.x - first.x) * (second.x - first.x) +
               (second.y - first.y) * (second.y - first.y);
    }

    static T dotProduct(Point const& first, Point const& second) {
        return first.x * second.x + first.y * second.y;
    }
};

template <Number T>
bool operator<(Point<T> const& first, Point<T> const& second);
template <Number T>
std::istream& operator>>(std::istream& is, Point<T>& p);
template <Number T>
std::ostream& operator<<(std::ostream& os, Point<T> const& p);
template <Number T>
bool operator==(Point<T> const& first, Point<T> const& second);
template <Number T>
bool operator!=(Point<T> const& first, Point<T> const& second);
template <Number T>
bool operator!=(Point<T> const& first, Point<T> const& second) {
    return !(first == second);
}
template <Number T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}
template <Number T>
std::ostream& operator<<(std::ostream& os, Point<T> const& p) {
    os << '(' << p.x << ' ' << p.y << ')';
    return os;
}

template <Number T>
struct Segment {
    Point<T> a, b;
    Segment() = default;
    explicit Segment(Point<T> const& first, Point<T> const& second) {
        if (first == second) {
            throw std::invalid_argument("Bad points");
        }
        if (first < second) {
            a = first;
            b = second;
        } else {
            a = second;
            b = first;
        }
    }
    double slope() const {
        if (!eq(a.x - b.x, static_cast<T>(0))) return (a.y - b.y) / (a.x - b.x);
        return std::numeric_limits<T>::max();
    }
    double legnth() const { return Point<T>::distance(a, b); }
    T legnthSquare() const { return Point<T>::distanceSquare(a, b); }
    static bool parallel(Segment const& first, Segment const& second) {
        return eq(first.slope(), second.slope());
    }
};
template <Number T>
bool operator==(Segment<T> const& first, Segment<T> const& second);
template <Number T>
bool operator!=(Segment<T> const& first, Segment<T> const& second);
template <Number T>
bool operator==(Segment<T> const& first, Segment<T> const& second) {
    return first.a == second.a && first.b == second.b;
}
template <Number T>
bool operator!=(Segment<T> const& first, Segment<T> const& second) {
    return !(first == second);
}

template <Number T>
class Figure {
   public:
    virtual Point<double> center() const noexcept = 0;
    explicit virtual operator double() const noexcept = 0;
    virtual ~Figure() noexcept = default;

   protected:
    virtual void input(std::istream& is) = 0;
    virtual void print(std::ostream& os) const = 0;

    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.input(is);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Figure const& fig) {
        fig.print(os);
        return os;
    }
};

template <Number T>
std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.input(is);
    return is;
}
template <Number T>
std::ostream& operator<<(std::ostream& os, Figure<T> const& fig) {
    fig.print(os);
    return os;
}
template <Number T>
bool operator==(Point<T> const& first, Point<T> const& second) {
    return eq(first.x, second.x) && eq(first.y, second.y);
}

template <Number T>
bool operator<(Point<T> const& first,
               Point<T> const& second) {  // checked unequality
    if (eq(first.x, second.x)) {
        return first.y < second.y;
    }
    return first.x < second.x;
}