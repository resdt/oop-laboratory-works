#pragma once
#include "figure.h"

class Square final : public Figure {
   public:
    explicit Square() = default;
    explicit Square(Point const& p1, Point const& p2);
    Point center() const noexcept override;
    explicit operator double() const noexcept override;

   private:
    Point a, b;
    void loadPoints(Point const& p1, Point const& p2);
    void input(std::istream& is) override;
    void print(std::ostream& os) const override;
    friend bool operator==(Square const& a, Square const& b);
};
