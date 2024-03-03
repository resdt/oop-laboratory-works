#pragma oncew
#include "figure.h"

template <Number T>
class Square final : public Figure<T> {
   public:
    explicit Square() = default;
    explicit Square(Point<T> const& p1, Point<T> const& p2) {
        loadPoints(p1, p2);
    }
    Point<double> center() const noexcept override {
        return Point{(static_cast<double>(a.x) + static_cast<double>(b.x)) / 2,
                     (static_cast<double>(a.y) + static_cast<double>(b.y)) / 2};
    }
    explicit operator double() const noexcept override {
        return Point<T>::distanceSquare(a, b) / 2;
    }

   private:
    Point<T> a, b;
    void loadPoints(Point<T> const& p1, Point<T> const& p2) {
        if (p1 == p2) {
            throw std::invalid_argument("Bad points");
        }
        if (p1.x < p2.x && p1.y < p2.y) {
            a = p1;
            b = p2;
        } else if (p1.x > p2.x && p1.y < p2.y) {
            a = {(p1.x + p2.x + p1.y - p2.y) / 2,
                 (p1.y + p2.y - p1.x + p2.x) / 2};
            b = {(p1.x + p2.x - p1.y + p2.y) / 2,
                 (p1.y + p2.y + p1.x - p2.x) / 2};
        } else if (p1.x < p2.x && p1.y > p2.y) {
            a = {(p1.x + p2.x - p1.y + p2.y) / 2,
                 (p1.y + p2.y + p1.x - p2.x) / 2};
            b = {(p1.x + p2.x + p1.y - p2.y) / 2,
                 (p1.y + p2.y - p1.x + p2.x) / 2};
        } else {
            a = p2;
            b = p1;
        }
    }

    void input(std::istream& is) override {
        Point<T> p1, p2;
        is >> p1 >> p2;
        loadPoints(p1, p2);
    }
    void print(std::ostream& os) const override {
        Point c{(a.x + b.x + a.y - b.y) / 2, (a.y + b.y - a.x + b.x) / 2};
        Point d{(a.x + b.x - a.y + b.y) / 2, (a.y + b.y + a.x - b.x) / 2};

        std::cout << "Square " << a << ' ' << c << ' ' << b << ' ' << d;
    }
    friend bool operator==(Square const& a, Square const& b) {
        return a.a == b.a && a.b == b.b;
    }
};
