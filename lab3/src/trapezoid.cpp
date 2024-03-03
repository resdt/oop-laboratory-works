#include "trapezoid.h"

Trapezoid::Trapezoid(Segment const& a, Segment const& b) { loadSegments(a, b); }
Point Trapezoid::center() const noexcept {
    return Point((lng.a.x + lng.b.x + shrt.a.x + shrt.b.x) / 4,
                 (lng.a.y + lng.b.y + shrt.a.y + shrt.b.y) / 4);
}
Trapezoid::operator double() const noexcept {
    auto p = shrt.a;
    auto l = lng;
    auto h =
        std::abs((l.b.y - l.a.y) * p.x - (l.b.x - l.a.x) * p.y + l.b.x * l.a.y -
                 l.a.x * l.b.y) /
        std::sqrt(std::pow((l.b.y - l.a.y), 2) + std::pow((l.b.x - l.a.x), 2));
    return (lng.legnth() + shrt.legnth()) * h / 2;
}

void Trapezoid::loadSegments(Segment const& a, Segment const& b) {
    if (a == b || !Segment::parallel(a, b)) {
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

void Trapezoid::input(std::istream& is) {
    Point p1, p2, p3, p4;
    is >> p1 >> p2 >> p3 >> p4;
    loadSegments(Segment(p1, p2), Segment(p3, p4));
}
void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid " << lng.a << lng.b << shrt.a << shrt.b;
}

bool operator==(Trapezoid const& tr1, Trapezoid const& tr2) {
    return tr1.lng == tr2.lng && tr1.shrt == tr2.shrt;
}