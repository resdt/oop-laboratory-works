#pragma once

#include <math.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>

#include "observer.h"
#include "visitor.h"

struct NPC;
struct Bear;
struct Elf;
struct Rogue;
using set_t = std::set<std::shared_ptr<NPC>>;

enum class NpcType { Unknown = 0, BearType = 1, ElfType = 2, RogueType = 3 };

struct NPC : public std::enable_shared_from_this<NPC> {
    NpcType type;
    int x{0};
    int y{0};
    std::string name;
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int _x, int _y, const std::string &name);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other,
                          size_t distance) const;
    virtual bool accept(std::shared_ptr<Visitor> v) = 0;

    virtual bool fight(std::shared_ptr<Bear> other) = 0;
    virtual bool fight(std::shared_ptr<Elf> other) = 0;
    virtual bool fight(std::shared_ptr<Rogue> other) = 0;
    virtual void print(std::ostream &os) = 0;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
    virtual ~NPC() = default;
};

set_t fight(const set_t &array, size_t distance);
std::ostream &operator<<(std::ostream &os, const set_t &array);