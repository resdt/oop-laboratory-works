#include "npc.h"

NPC::NPC(NpcType t, int _x, int _y, const std::string &name)
    : type(t), x(_x), y(_y), name(name) {}
NPC::NPC(NpcType t, std::istream &is) : type(t) {
    is >> name;
    is >> x;
    is >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto &o : observers) o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <=
        std::pow(distance, 2))
        return true;
    else
        return false;
}

void NPC::save(std::ostream &os) {
    os << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << npc.name << " { x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}

std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array) n->print(std::cout);
    return os;
}

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                (attacker->is_close(defender, distance))) {
                bool success{false};
                auto v = std::make_shared<FightVisitor>(attacker);
                success = defender->accept(v);
                if (success) dead_list.insert(defender);
            }

    return dead_list;
}