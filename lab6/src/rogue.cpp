#include "rogue.h"

#include "bear.h"
#include "elf_.h"
#include "visitor.h"

Rogue::Rogue(int x, int y, const std::string &name) : NPC(NpcType::RogueType, x, y, name) {}
Rogue::Rogue(std::istream &is) : NPC(NpcType::RogueType, is) {}


void Rogue::print(std::ostream &os) { os << *this; }

bool Rogue::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false);
    return false;
}

bool Rogue::fight(std::shared_ptr<Rogue> other) {
    fight_notify(other, true);
    return true;
}

bool Rogue::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

bool Rogue::accept(std::shared_ptr<Visitor> v) {
    return v->visit(std::static_pointer_cast<Rogue>(shared_from_this()));
}

void Rogue::save(std::ostream &os) {
    os << static_cast<int>(NpcType::RogueType) << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Rogue &elf) {
    os << "rogue: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}