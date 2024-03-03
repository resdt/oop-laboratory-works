#include "bear.h"

#include "elf_.h"
#include "rogue.h"
#include "visitor.h"

Bear::Bear(int x, int y, const std::string &name) : NPC(NpcType::BearType, x, y, name) {}
Bear::Bear(std::istream &is) : NPC(NpcType::BearType, is) {}

void Bear::print(std::ostream &os) { os << *this; }

void Bear::save(std::ostream &os) {
    os << static_cast<int>(NpcType::BearType) << std::endl;
    NPC::save(os);
}

bool Bear::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false);
    return false;
}

bool Bear::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, true);
    return true;
}

bool Bear::fight(std::shared_ptr<Rogue> other) {
    fight_notify(other, false);
    return false;
}

bool Bear::accept(const std::shared_ptr<Visitor> v) {
    return v->visit(std::static_pointer_cast<Bear>(shared_from_this()));
}

std::ostream &operator<<(std::ostream &os, Bear &bear) {
    os << "bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}