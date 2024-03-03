#pragma once

#include <cmath>
#include <iostream>

inline bool eq(double lhs, double rhs, double epsilon = 1e-6) {
    return std::abs(lhs - rhs) < epsilon;
}

struct Point {
    double x, y;
    Point();
    Point(double x, double y);
    static double distance(Point const& first, Point const& second = {0, 0});
    static double distanceSquare(Point const& first,
                                 Point const& second = {0, 0});
    static double dotProduct(Point const& first, Point const& second);
};
bool operator<(Point const& first, Point const& second);

std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, Point const& p);
bool operator==(Point const& first, Point const& second);
bool operator!=(Point const& first, Point const& second);

struct Segment {
    Point a, b;
    Segment() = default;
    explicit Segment(Point const& first, Point const& second);
    double legnth() const;
    double legnthSquare() const;
    double slope() const;
    static bool parallel(Segment const& first, Segment const& second);
};
bool operator==(Segment const& first, Segment const& second);
bool operator!=(Segment const& first, Segment const& second);

class Figure {
   public:
    virtual Point center() const noexcept = 0;
    explicit virtual operator double() const noexcept = 0;
    virtual ~Figure() noexcept = default;

   protected:
    virtual void input(std::istream& is) = 0;
    virtual void print(std::ostream& os) const = 0;

    friend std::istream& operator>>(std::istream& is, Figure& fig);
    friend std::ostream& operator<<(std::ostream& os, Figure const& fig);
};
