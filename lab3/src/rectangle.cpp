#include "rectangle.h"

Rectangle::Rectangle(Segment const& diag, Point const& a) {
    loadPoints(diag, a);
}

Rectangle::Rectangle(Point const& a, Segment const& diag)
    : Rectangle(diag, a) {}

Point Rectangle::center() const noexcept {
    return Point{(diag.a.x + diag.b.x) / 2, (diag.a.y + diag.b.y) / 2};
}
Rectangle::operator double() const noexcept {
    return std::sqrt(Point::distanceSquare(a, diag.a) *
                     Point::distanceSquare(a, diag.b));
}

void Rectangle::input(std::istream& is) {
    Point a, b, c;
    is >> a >> b >> c;
    loadPoints(Segment(a, b), c);
}
void Rectangle::print(std::ostream& os) const {
    auto b = Point{diag.a.x + diag.b.x - a.x, diag.a.y + diag.b.y - a.y};
    os << "Rectangle " << diag.a << ' ' << a << ' ' << diag.b << ' ' << b;
}

void Rectangle::loadPoints(Segment const& diag, Point const& p) {
    auto cat1 = Point::distance(p, diag.a);
    auto cat2 = Point::distance(p, diag.b);
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
        Segment newDiag {a,b};
        this->diag = newDiag;
        a = p1;
        b = p2;
    } else if (p1.x < p2.x && p1.y > p2.y) {
        Segment newDiag {a,b};
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

bool operator==(Rectangle const& rec1, Rectangle const& rec2) {
    return rec1.a == rec2.a && rec1.diag == rec2.diag;
}
