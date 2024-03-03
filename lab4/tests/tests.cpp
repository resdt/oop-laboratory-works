#include <gtest/gtest.h>

#include <memory>

#include "figure.h"
#include "figure_array.h"
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"

TEST(lab3, square) {
    EXPECT_EQ(Square<int>({0, 0}, {2, 2}), Square<int>({0, 2}, {2, 0}));
    EXPECT_TRUE(
        eq(static_cast<double>(Square<double>({0, 2}, {2, 3.4})), 2.98));
    EXPECT_EQ(Square<int>({-1, -1}, {0, 0}).center(), (Point{-0.5, -0.5}));
}

TEST(lab3, rectangle) {
    auto rec1 =
        Rectangle<long>(Point<long>{0, 1}, Segment<long>{{0, 0}, {1, 1}});
    auto rec2 =
        Rectangle<long>(Segment<long>{{1, 1}, {0, 0}}, Point<long>{0, 1});
    auto rec3 =
        Rectangle<long>(Segment<long>{{0, 1}, {1, 0}}, Point<long>{0, 0});
    auto rec4 =
        Rectangle<long>(Segment<long>{{0, 1}, {1, 0}}, Point<long>{1, 1});

    EXPECT_EQ(rec1, rec2);
    EXPECT_EQ(rec1, rec3);
    EXPECT_EQ(rec1, rec4);

    EXPECT_TRUE(eq(static_cast<double>(rec1), 1.));
    EXPECT_EQ(rec1.center(), Point<double>(0.5, 0.5));

    rec1 = Rectangle<long>(Point<long>{0, 1}, Segment<long>{{0, 0}, {2, 1}});
    rec2 = Rectangle<long>(Segment<long>{{2, 1}, {0, 0}}, Point<long>{0, 1});
    rec3 = Rectangle<long>(Segment<long>{{0, 1}, {2, 0}}, Point<long>{0, 0});
    rec4 = Rectangle<long>(Segment<long>{{2, 0}, {0, 1}}, Point<long>{2, 1});

    EXPECT_EQ(rec1, rec2);
    EXPECT_EQ(rec1, rec3);
    EXPECT_EQ(rec1, rec4);

    EXPECT_TRUE(eq(static_cast<double>(rec1), 2.));
    EXPECT_EQ(rec1.center(), Point<double>(1, 0.5));

    auto rec_d =
        Rectangle<double>(Segment<double>({0, 0}, {4, 0}), {1, -std::sqrt(3)});
    EXPECT_TRUE(eq(static_cast<double>(rec_d), 6.92820323));
    EXPECT_EQ(rec_d.center(), Point<double>(2, 0));
}

TEST(lab3, trapezoid) {
    auto tr1 = Trapezoid<int>{Segment<int>{{0, 0}, {1, 1}},
                              Segment<int>{{0, -3}, {6, 3}}};
    auto tr2 = Trapezoid<int>{Segment<int>{{0, -3}, {6, 3}},
                              Segment<int>{{1, 1}, {0, 0}}};
    EXPECT_EQ(tr1, tr2);
    EXPECT_TRUE(eq(static_cast<double>(tr1), static_cast<double>(tr2)));
    EXPECT_TRUE(eq(static_cast<double>(tr1), 10.5));
    auto tr3 = Trapezoid<double>{Segment<double>{{0, 0}, {2, 0}},
                                 Segment<double>{{0.5, 1}, {1.5, 1}}};
    EXPECT_EQ(static_cast<double>(tr3), 1.5);
    EXPECT_EQ(tr3.center(), (Point<double>{1, 0.5}));
}

TEST(lab3, array) {
    auto fig1 = std::make_shared<Square<double>>(Point<double>{0, 0},
                                                 Point<double>{2, 2});
    auto fig2 = std::make_shared<Square<double>>(Point<double>{0, 2},
                                                 Point<double>{2, 0});
    auto fig3 = std::make_shared<Rectangle<double>>(
        Segment<double>{{0, 1}, {1, 0}}, Point<double>{0, 0});
    auto fig4 = std::make_shared<Trapezoid<double>>(
        Segment<double>{{0, 0}, {2, 0}}, Segment<double>{{0.5, 1}, {1.5, 1}});

    Array<std::shared_ptr<Figure<double>>> arr{fig1, fig2, fig3, fig4};
    EXPECT_TRUE(eq(arr.sumOfSquares(), 4 + 4 + 1 + 1.5));
    arr.pushBack(fig1);
    arr.pushBack(fig2);
    arr.pushBack(fig3);
    arr.pushBack(fig4);
    EXPECT_TRUE(eq(arr.sumOfSquares(), (4 + 4 + 1 + 1.5) * 2));
    arr.erase(1);
    EXPECT_TRUE(eq(arr.sumOfSquares(), (4 + 4 + 1 + 1.5) * 2 - 4));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}