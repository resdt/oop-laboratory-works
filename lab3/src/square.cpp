#include "square.h"

Square::Square(Point const& p1, Point const& p2) { loadPoints(p1, p2); }
Point Square::center() const noexcept {
    return Point{(a.x + b.x) / 2, (a.y + b.y) / 2};
}
Square::operator double() const noexcept {
    return Point::distanceSquare(a, b) / 2;
}

void Square::input(std::istream& is) {
    Point p1, p2;
    is >> p1 >> p2;
    loadPoints(p1, p2);
}
void Square::print(std::ostream& os) const {
    Point c{(a.x + b.x + a.y - b.y) / 2, (a.y + b.y - a.x + b.x) / 2};
    Point d{(a.x + b.x - a.y + b.y) / 2, (a.y + b.y + a.x - b.x) / 2};

    std::cout << "Square " << a << ' ' << c << ' ' << b << ' ' << d;
}

bool operator==(Square const& a, Square const& b) {
    return a.a == b.a && a.b == b.b;
}

void Square::loadPoints(Point const& p1, Point const& p2) {
    if (p1 == p2) {
        throw std::invalid_argument("Bad points");
    }
    if (p1.x < p2.x && p1.y < p2.y) {
        a = p1;
        b = p2;
    } else if (p1.x > p2.x && p1.y < p2.y) {
        a = {(p1.x + p2.x + p1.y - p2.y) / 2, (p1.y + p2.y - p1.x + p2.x) / 2};
        b = {(p1.x + p2.x - p1.y + p2.y) / 2, (p1.y + p2.y + p1.x - p2.x) / 2};
    } else if (p1.x < p2.x && p1.y > p2.y) {
        a = {(p1.x + p2.x - p1.y + p2.y) / 2, (p1.y + p2.y + p1.x - p2.x) / 2};
        b = {(p1.x + p2.x + p1.y - p2.y) / 2, (p1.y + p2.y - p1.x + p2.x) / 2};
    } else {
        a = p2;
        b = p1;
    }
}
