#pragma once

#include "figure.h"

class Trapezoid final : public Figure {
   public:
    Trapezoid() = default;
    explicit Trapezoid(Segment const& a, Segment const& b);
    Point center() const noexcept override;
    explicit operator double() const noexcept override;

   private:
    Segment lng, shrt;
    void loadSegments(Segment const& a, Segment const& b);
    void input(std::istream& is) override;
    void print(std::ostream& os) const override;
    friend bool operator==(Trapezoid const& tr1, Trapezoid const& tr2);
};
