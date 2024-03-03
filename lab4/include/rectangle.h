#pragma once
#include "figure.h"

template <Number T>
class Rectangle final : public Figure<T> {
   public:
    Rectangle() = default;
    explicit Rectangle(Segment<T> const& diag, Point<T> const& a) {
        loadPoints(diag, a);
    }
    explicit Rectangle(Point<T> const& a, Segment<T> const& diag)
        : Rectangle(diag, a) {}

    Point<double> center() const noexcept override {
        return Point{
            (static_cast<double>(diag.a.x) + static_cast<double>(diag.b.x)) / 2,
            (static_cast<double>(diag.a.y) + static_cast<double>(diag.b.y)) / 2};
    }
    explicit operator double() const noexcept override {
        return std::sqrt(Point<T>::distanceSquare(a, diag.a) *
                         Point<T>::distanceSquare(a, diag.b));
    }

    friend bool operator==(Rectangle const& rec1, Rectangle const& rec2) {
        return rec1.a == rec2.a && rec1.diag == rec2.diag;
    }

   private:
    Point<T> a;
    Segment<T> diag;
    void loadPoints(Segment<T> const& diag, Point<T> const& p) {
        auto cat1 = Point<T>::distance(p, diag.a);
        auto cat2 = Point<T>::distance(p, diag.b);
        auto hypot = diag.legnth();

        if (eq(hypot, cat1 + cat2) ||
            !eq(hypot * hypot, cat1 * cat1 + cat2 * cat2)) {
            throw std::invalid_argument("Bad params");
        }

        auto a = p;
        auto b = Point{diag.a.x + diag.b.x - a.x, diag.a.y + diag.b.y - a.y};
        auto p1 = diag.a;
        auto p2 = diag.b;

        if (p1.x < p2.x && p1.y < p2.y) {
            this->diag.a = p1;
            this->diag.b = p2;
        } else if (p1.x > p2.x && p1.y < p2.y) {
            Segment newDiag{a, b};
            this->diag = newDiag;
            a = p1;
            b = p2;
        } else if (p1.x < p2.x && p1.y > p2.y) {
            Segment newDiag{a, b};
            this->diag = newDiag;
            a = p2;
            b = p1;
        } else {
            this->diag.a = p2;
            this->diag.b = p1;
        }

        if (this->diag.a.y < a.y) {
            this->a = a;
        } else {
            this->a = b;
        }
    }
    void input(std::istream& is) override {
        Point<T> a, b, c;
        is >> a >> b >> c;
        loadPoints(Segment(a, b), c);
    }
    void print(std::ostream& os) const override {
        auto b = Point{diag.a.x + diag.b.x - a.x, diag.a.y + diag.b.y - a.y};
        os << "Rectangle " << diag.a << ' ' << a << ' ' << diag.b << ' ' << b;
    }
};
