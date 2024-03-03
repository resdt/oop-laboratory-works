#pragma once

#include <math.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <shared_mutex>
#include <string>
#include "observer.h"
// type for npcs
struct NPC;
struct Elf;
struct Rogue;
struct Bear;
using set_t = std::set<std::shared_ptr<NPC>>;

enum class NpcType { Unknown = 0, ElfType = 1, RogueType = 2, BearType = 3 };

class NPC {
   private:
    std::mutex mtx;

    NpcType type;
    int x{0};
    int y{0};
    bool alive{true};

    std::vector<std::shared_ptr<IFightObserver>> observers;

   protected:
    bool is_close(const std::shared_ptr<NPC> &other, size_t distance);

   public:
    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other) = 0;

    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    // visit
    virtual bool fight(std::shared_ptr<Elf> other) = 0;
    virtual bool fight(std::shared_ptr<Rogue> other) = 0;
    virtual bool fight(std::shared_ptr<Bear> other) = 0;

    virtual void print() = 0;
    std::pair<int, int> position();
    NpcType get_type();

    virtual void save(std::ostream &os);
    virtual int get_move_distance() = 0;
    friend std::ostream &operator<<(std::ostream &os, NPC &npc);

    void move(int shift_x, int shift_y, int max_x, int max_y);

    bool is_alive();
    void must_die();
};