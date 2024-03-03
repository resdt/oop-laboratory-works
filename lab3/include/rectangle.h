#pragma once
#include "figure.h"

class Rectangle final : public Figure {
   public:
    Rectangle() = default;
    explicit Rectangle(Segment const& diag, Point const& a);
    explicit Rectangle(Point const& a,Segment const& diag);
    Point center() const noexcept override;
    explicit operator double() const noexcept override;

   private:
    Point a;
    Segment diag;
    void loadPoints(Segment const& diag, Point const& a);
    void input(std::istream& is) override;
    void print(std::ostream& os) const override;
    friend bool operator==(Rectangle const& rec1, Rectangle const& rec2);
};
