#include <gtest/gtest.h>

#include "figure.h"
#include "figure_array.h"
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"

TEST(lab3, square) {
    EXPECT_EQ(Square({0, 0}, {2, 2}), Square({0, 2}, {2, 0}));
    EXPECT_TRUE(eq(static_cast<double>(Square({0, 2}, {2, 3.4})), 2.98));
    EXPECT_EQ(Square({-1, -1}, {0, 0}).center(), (Point{-0.5, -0.5}));
}

TEST(lab3, rectangle) {
    auto rec1 = Rectangle(Point{0, 1}, Segment{{0, 0}, {1, 1}});
    auto rec2 = Rectangle(Segment{{1, 1}, {0, 0}}, Point{0, 1});
    auto rec3 = Rectangle(Segment{{0, 1}, {1, 0}}, Point{0, 0});
    auto rec4 = Rectangle(Segment{{0, 1}, {1, 0}}, Point{1, 1});

    EXPECT_EQ(rec1, rec2);
    EXPECT_EQ(rec1, rec3);
    EXPECT_EQ(rec1, rec4);

    EXPECT_TRUE(eq(static_cast<double>(rec1), 1));
    EXPECT_EQ(rec1.center(), Point(0.5, 0.5));

    rec1 = Rectangle(Point{0, 1}, Segment{{0, 0}, {2, 1}});
    rec2 = Rectangle(Segment{{2, 1}, {0, 0}}, Point{0, 1});
    rec3 = Rectangle(Segment{{0, 1}, {2, 0}}, Point{0, 0});
    rec4 = Rectangle(Segment{{2, 0}, {0, 1}}, Point{2, 1});

    EXPECT_EQ(rec1, rec2);
    EXPECT_EQ(rec1, rec3);
    EXPECT_EQ(rec1, rec4);

    EXPECT_TRUE(eq(static_cast<double>(rec1), 2));
    EXPECT_EQ(rec1.center(), Point(1, 0.5));

    rec1 = Rectangle(Segment({0, 0}, {4, 0}), {1, -std::sqrt(3)});
    EXPECT_TRUE(eq(static_cast<double>(rec1), 6.92820323));
    EXPECT_EQ(rec1.center(), Point(2, 0));
}

TEST(lab3, trapezoid) {
    auto tr1 = Trapezoid{Segment{{0, 0}, {1, 1}}, Segment{{0, -3}, {6, 3}}};
    auto tr2 = Trapezoid{Segment{{0, -3}, {6, 3}}, Segment{{1, 1}, {0, 0}}};
    EXPECT_EQ(tr1, tr2);
    EXPECT_TRUE(eq(static_cast<double>(tr1), static_cast<double>(tr2)));
    EXPECT_TRUE(eq(static_cast<double>(tr1), 10.5));
    auto tr3 = Trapezoid{Segment{{0, 0}, {2, 0}}, Segment{{0.5, 1}, {1.5, 1}}};
    EXPECT_EQ(static_cast<double>(tr3), 1.5);
    EXPECT_EQ(tr3.center(), (Point{1, 0.5}));
}

TEST(lab3, array) {
    auto fig1 = Square({0, 0}, {2, 2});
    auto fig2 = Square({0, 2}, {2, 0});
    auto fig3 = Rectangle(Segment{{0, 1}, {1, 0}}, Point{0, 0});
    auto fig4 = Trapezoid{Segment{{0, 0}, {2, 0}}, Segment{{0.5, 1}, {1.5, 1}}};

    FigureArray arr{&fig1, &fig2, &fig3, &fig4};
    EXPECT_TRUE(eq(arr.sumOfSquares(), 4 + 4 + 1 + 1.5));
    arr.pushBack(&fig1);
    arr.pushBack(&fig2);
    arr.pushBack(&fig3);
    arr.pushBack(&fig4);
    EXPECT_TRUE(eq(arr.sumOfSquares(), (4 + 4 + 1 + 1.5) * 2));
    arr.erase(1);
    EXPECT_TRUE(eq(arr.sumOfSquares(), (4 + 4 + 1 + 1.5) * 2 - 4));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}