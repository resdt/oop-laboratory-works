#include "figure.h"

#include <limits>

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.input(is);
    return is;
}
std::ostream& operator<<(std::ostream& os, Figure const& fig) {
    fig.print(os);
    return os;
}

bool operator==(Point const& first, Point const& second) {
    return eq(first.x, second.x) && eq(first.y, second.y);
}
bool operator!=(Point const& first, Point const& second) {
    return !(first == second);
}

Point::Point() : x(0), y(0){};

Point::Point(double x, double y) : x(x), y(y){};

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}
std::ostream& operator<<(std::ostream& os, Point const& p) {
    os << '(' << p.x << ' ' << p.y << ')';
    return os;
}

Segment::Segment(Point const& first, Point const& second) {
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

double Point::distance(Point const& first, Point const& second) {
    return std::sqrt((second.x - first.x) * (second.x - first.x) +
                     (second.y - first.y) * (second.y - first.y));
}

double Point::distanceSquare(Point const& first, Point const& second) {
    return (second.x - first.x) * (second.x - first.x) +
           (second.y - first.y) * (second.y - first.y);
}

double Segment::slope() const {
    if (!eq(a.x - b.x, 0)) return (a.y - b.y) / (a.x - b.x);
    return std::numeric_limits<double>::max();
}

double Segment::legnth() const { return Point::distance(a, b); }

double Segment::legnthSquare() const { return Point::distanceSquare(a, b); }


bool Segment::parallel(Segment const& first, Segment const& second) {
    return eq(first.slope(), second.slope());
}

double Point::dotProduct(Point const& first, Point const& second) {
    return first.x * second.x + first.y * second.y;
}

bool operator==(Segment const& first, Segment const& second) {
    return first.a == second.a && first.b == second.b;
}
bool operator!=(Segment const& first, Segment const& second) {
    return !(first == second);
}

bool operator<(Point const& first,
               Point const& second) {  // checked unequality
    if (eq(first.x, second.x)) {
        return first.y < second.y;
    }
    return first.x < second.x;
}