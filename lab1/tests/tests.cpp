#include <gtest/gtest.h>

#include "task.h"

TEST(remove_vowels, test1) {
    std::string s = "";
    ASSERT_TRUE(removeVowels(s) == "");
}

TEST(remove_vowels, test2) {
    std::string s = "iu io wo";
    ASSERT_TRUE(removeVowels(s) == "  w");
}

TEST(remove_vowels, test3) {
    std::string s = "abc qwert";
    ASSERT_TRUE(removeVowels(s) == "bc qwrt");
}

TEST(remove_vowels, test4) {
    std::string s = "ABC";
    ASSERT_TRUE(removeVowels(s) == "BC");
}

TEST(remove_vowels, test5) {
    std::string s = "testing::InitGoogleTest";
    ASSERT_TRUE(removeVowels(s) == "tstng::ntGglTst");
}

TEST(remove_vowels, test6) {
    std::string s = "This website is for losers LOL!";
    ASSERT_FALSE(removeVowels(s) == "Ths wbst s fr losrs LL!");
}

TEST(remove_vowels, test7) {
    std::string s = "ABC";
    ASSERT_TRUE(removeVowelsByRef(s) == "BC");
}

TEST(remove_vowels, test8) {
    std::string s = "testing::InitGoogleTest";
    ASSERT_TRUE(removeVowelsByRef(s) == "tstng::ntGglTst");
}

TEST(remove_vowels, test9) {
    std::string s = "This website is for losers LOL!";
    ASSERT_FALSE(removeVowelsByRef(s) == "Ths wbst s fr losrs LL!");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}