#pragma once
#include "npc.h"

struct Rogue : public NPC {
    Rogue(int x, int y,const std::string &name);
    Rogue(std::istream &is);
    void print(std::ostream &os) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Rogue> other) override;

    bool accept(std::shared_ptr<Visitor> v) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Rogue &rogue);
};