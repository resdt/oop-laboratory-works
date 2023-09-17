#include <gtest/gtest.h>
#include "functions.cpp"

TEST(TimeTest, Test1) {
   EXPECT_EQ(hour_format("12:00 pm"), "0000");
   EXPECT_EQ(hour_format("12:01 pm"), "0001");
   EXPECT_EQ(hour_format("10:01 pm"), "2201");
   EXPECT_EQ(hour_format("12:00 am"), "1200");
   EXPECT_EQ(hour_format("1:00 pm"), "1300");
   EXPECT_EQ(hour_format("12:00 pm"), "0000");
}
