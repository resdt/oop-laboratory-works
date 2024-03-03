#include <gtest/gtest.h>

#include "money.h"

using namespace xyz;

TEST(money, test1) {
    Money m1(3, '7');
    Money m2("3.12");
    ASSERT_TRUE((m1 + m2).toString() == "10.89");
}

TEST(money, test2) {
    Money m1("03.12");
    Money m2("3.12");
    ASSERT_FALSE(m1 < m2);
}

TEST(money, test3) {
    Money m1{'1', '0', '0', '0'};
    Money m2("3.22");
    ASSERT_TRUE((m1 - m2) == Money("6.78"));
}

TEST(money, test4) {
    Money m1{"1000000.00"};
    Money m2("0.01");
    ASSERT_TRUE((m1 - m2) == Money("999999.99"));
}

TEST(money, test5) {
    Money m1{"1002000.00"};
    Money m2("0.10");
    ASSERT_TRUE((m1 + m2) == (m1+m2) );
    ASSERT_TRUE(m1 +m2 == Money("1002000.10"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}