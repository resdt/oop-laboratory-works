#pragma once
#include "npc.h"

struct Bear : public NPC
{
    Bear(int x, int y);
    Bear(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Rogue> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    bool is_close(const std::shared_ptr<NPC> &other) override;
    int get_move_distance() override;

    friend std::ostream &operator<<(std::ostream &os, Bear &rogue);
};