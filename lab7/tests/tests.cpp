#include <gtest/gtest.h>

#include "bear.h"
#include "elf_.h"
#include "factory.h"
#include "npc.h"
#include "rogue.h"

TEST(FightTest1, BearVsElf) {
    auto bear = factory(NpcType::BearType, 0, 0);
    auto elf = factory(NpcType::ElfType, 1, 1);
    ASSERT_FALSE(bear->accept(elf));
}

TEST(FightTest2, RogueVsBear) {
    auto bear = factory(NpcType::BearType, 0, 0);
    auto rogue = factory(NpcType::RogueType, 1, 1);
    ASSERT_FALSE(rogue->accept(bear));
}

TEST(FightTest2, RangeTest) {
    auto rogue = factory(NpcType::RogueType, 0, 0);
    auto elf = factory(NpcType::ElfType, 40, 30);
    ASSERT_FALSE(rogue->is_close(elf));
    ASSERT_TRUE(elf->is_close(rogue));
}

TEST(FightTest2, MoveTest) {
    auto bear = factory(NpcType::BearType, 0, 0);
    auto elf = factory(NpcType::ElfType, 6, 6);
    ASSERT_FALSE(bear->is_close(elf));
    bear->move(bear->get_move_distance(), 0, 100, 100);
    ASSERT_TRUE(elf->is_close(bear));
}

TEST(FightTest2, MainFighting) {
    set_t NPCs;
    NPCs.insert(factory(NpcType::ElfType, 0, 0));  // dead
    NPCs.insert(factory(NpcType::BearType, 5, 5));
    NPCs.insert(factory(NpcType::RogueType, 10, 10));  // dead
    NPCs.insert(factory(NpcType::RogueType, -52, -52));
    NPCs.insert(factory(NpcType::BearType, 101, 101));
    NPCs.insert(factory(NpcType::ElfType, 100, 100));  // dead

    set_t NPCsKilled;

    for (auto& attacker : NPCs) {
        for (auto& defender : NPCs) {
            if (attacker->is_alive())
                if (defender->is_alive())
                    if ((attacker->is_close(defender)))
                        if (defender->accept(attacker)) {
                            defender->must_die();
                            NPCsKilled.insert(defender);
                        }
        }
    }

    ASSERT_EQ(3, NPCsKilled.size());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}