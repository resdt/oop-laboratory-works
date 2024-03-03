#pragma once
#include "npc.h"

struct Rogue : public NPC
{
    Rogue(int x, int y);
    Rogue(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Rogue> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool is_close(const std::shared_ptr<NPC> &other) override;
    int get_move_distance() override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    friend std::ostream &operator<<(std::ostream &os, Rogue &rogue);
};