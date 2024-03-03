#include <gtest/gtest.h>

#include "bear.h"
#include "elf_.h"
#include "factory.h"
#include "npc.h"
#include "rogue.h"
#include "visitor.h"

TEST(FightTest1, Fighting) {
    Bear bear(10, 40, "Bear");
    Elf elf(5, 5, "Elf");
    Rogue rogue(0, 50, "Rogue");

    EXPECT_FALSE(elf.fight(std::make_shared<Bear>(bear)));
    EXPECT_TRUE(elf.fight(std::make_shared<Rogue>(rogue)));
    EXPECT_TRUE(bear.fight(std::make_shared<Elf>(elf)));
    EXPECT_FALSE(bear.fight(std::make_shared<Rogue>(rogue)));
    EXPECT_FALSE(rogue.fight(std::make_shared<Bear>(bear)));
    EXPECT_TRUE(rogue.fight(std::make_shared<Rogue>(rogue)));
}

TEST(FightTest2, MainFighting) {
    set_t array;

    array.insert(factory(NpcType::RogueType, 0, 0, "Valeera"));
    array.insert(factory(NpcType::RogueType, 10, 10, "Tess"));
    array.insert(factory(NpcType::RogueType, 15, -15, "VanCleef"));
    array.insert(factory(NpcType::ElfType, 30, 0, "Malfurion"));
    array.insert(factory(NpcType::RogueType, 30, 1, "Maiev"));
    array.insert(factory(NpcType::ElfType, 30, -20, "Tyrande"));
    array.insert(factory(NpcType::BearType, 40, -20, "Misha"));

    auto dead_list = fight(array, 20);
    for (auto &d : dead_list) array.erase(d);

    EXPECT_EQ(array.size(), 2);
}

TEST(VisitorTest, Visitor) {
    auto bear = std::make_shared<Bear>(0, 5, "Bear");
    auto elf = std::make_shared<Elf>(10, 20, "Elf");
    auto rogue = std::make_shared<Rogue>(5, 10, "Rogue");

    auto npcVisitor = std::make_shared<FightVisitor>(bear);

    EXPECT_FALSE(bear->accept(npcVisitor));
    EXPECT_TRUE(elf->accept(npcVisitor));
    EXPECT_FALSE(rogue->accept(npcVisitor));

    npcVisitor = std::make_shared<FightVisitor>(elf);

    EXPECT_FALSE(bear->accept(npcVisitor));
    EXPECT_FALSE(elf->accept(npcVisitor));
    EXPECT_TRUE(rogue->accept(npcVisitor));

    npcVisitor = std::make_shared<FightVisitor>(rogue);

    EXPECT_FALSE(bear->accept(npcVisitor));
    EXPECT_FALSE(elf->accept(npcVisitor));
    EXPECT_TRUE(rogue->accept(npcVisitor));
}

TEST(ObserverTest, Observer) {
    auto rogue = std::make_shared<Rogue>(0, 5, "Rogue");
    auto elf = std::make_shared<Elf>(5, 10, "Elf");

    testing::internal::CaptureStdout();

    auto textObserver = TextObserver::get();
    elf->subscribe(textObserver);
    elf->fight(rogue);

    std::string textOutput = testing::internal::GetCapturedStdout();
    std::string expectedOutput =
        "\nMurder ---------------\nelf: Elf { x:5, y:10} \nrogue: Rogue { x:0, y:5} \n";

    EXPECT_EQ(textOutput, expectedOutput);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}