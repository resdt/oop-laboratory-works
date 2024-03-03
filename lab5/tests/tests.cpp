#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <vector>

#include "allocator.h"
#include "vector.h"

using namespace lab5;

static int fact(int n) {
    if (n == 0) return 1;
    int result = 1;
    for (; n > 0; n--) {
        result *= n;
    }
    return result;
}

TEST(Lab5, AllocatorMapTest) {
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>>> m;
    m[0] = 1;
    for (int i = 1; i < 10; i++) {
        m[i] = m[i - 1] * i;
    }
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(m[i], fact(i));
    }
}

TEST(Lab5, VectorTest) {
    Vector<int> a = {0, 1, 2, 3, 4};
    a.pushBack(5);
    a.pushBack(6);
    int sum = 0;
    for (const auto& i : a) {
        sum += i;
    }
    EXPECT_EQ(sum, 21);
    std::vector<int> a2{0, 1, 2, 3, 4, 5, 6};
    for (int i = 0; i < a2.size(); ++i) {
        ASSERT_EQ(a[i],a2[i]);
    }
}

TEST(Lab5, VectorAllocatorTest) {
    Vector<int, Allocator<int>> a = {0, 1, 2, 3, 4};
    a.pushBack(5);
    a.pushBack(6);
    int sum = 0;
    for (const auto& i : a) {
        sum += i;
    }
    EXPECT_EQ(sum, 21);
    std::vector<std::string> arr = {"a", "1", "123"};
    Vector<std::string, Allocator<std::string>> copy;
    for (size_t i = 0; i < arr.size(); i++) {
        copy.pushBack(arr[i]);
    }
    for (size_t i = 0; i < copy.size(); i++) {
        EXPECT_EQ(arr[i], copy[i]);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}