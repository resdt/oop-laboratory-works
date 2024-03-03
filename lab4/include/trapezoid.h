#pragma once

#include "figure.h"
template <Number T>
class Trapezoid final : public Figure<T> {
   public:
    Trapezoid() = default;
    explicit Trapezoid(Segment<T> const& a, Segment<T> const& b) {
        loadSegments(a, b);
    }
    Point<double> center() const noexcept override {
        return Point(
            (static_cast<double>(lng.a.x) + static_cast<double>(lng.b.x) +
             static_cast<double>(shrt.a.x) + static_cast<double>(shrt.b.x)) /
                4,
            (static_cast<double>(lng.a.y) + static_cast<double>(lng.b.y) +
             static_cast<double>(shrt.a.y) + static_cast<double>(shrt.b.y)) /
                4);
    }
    explicit operator double() const noexcept override {
        auto p = shrt.a;
        auto l = lng;
        auto h = std::abs((l.b.y - l.a.y) * p.x - (l.b.x - l.a.x) * p.y +
                          l.b.x * l.a.y - l.a.x * l.b.y) /
                 std::sqrt(std::pow((l.b.y - l.a.y), 2) +
                           std::pow((l.b.x - l.a.x), 2));
        return (lng.legnth() + shrt.legnth()) * h / 2;
    }

   private:
    Segment<T> lng, shrt;
    void loadSegments(Segment<T> const& a, Segment<T> const& b) {
        if (a == b || !Segment<T>::parallel(a, b)) {
            throw std::invalid_argument("Bad segments");
        }
        if (a.legnth() > b.legnth()) {
            lng = a;
            shrt = b;
        } else {
            lng = b;
            shrt = a;
        }
    }
    void input(std::istream& is) override {
        Point<T> p1, p2, p3, p4;
        is >> p1 >> p2 >> p3 >> p4;
        loadSegments(Segment(p1, p2), Segment(p3, p4));
    }
    void print(std::ostream& os) const override {
        os << "Trapezoid " << lng.a << lng.b << shrt.a << shrt.b;
    }
    friend bool operator==(Trapezoid const& tr1, Trapezoid const& tr2) {
        return tr1.lng == tr2.lng && tr1.shrt == tr2.shrt;
    }
};
