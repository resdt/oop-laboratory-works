#include "elf_.h"

#include "bear.h"
#include "rogue.h"
#include "visitor.h"

Elf::Elf(int x, int y, const std::string &name)
    : NPC(NpcType::ElfType, x, y, name) {}
Elf::Elf(std::istream &is) : NPC(NpcType::ElfType, is) {}

void Elf::print(std::ostream &os) { os << *this; }

void Elf::save(std::ostream &os) {
    os << static_cast<int>(NpcType::ElfType) << std::endl;
    NPC::save(os);
}

bool Elf::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false);
    return false;
}

bool Elf::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

bool Elf::fight(std::shared_ptr<Rogue> other) {
    fight_notify(other, true);
    return true;
}

bool Elf::accept(std::shared_ptr<Visitor> v) {
    return v->visit(std::static_pointer_cast<Elf>(shared_from_this()));
}


std::ostream &operator<<(std::ostream &os, Elf &elf) {
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}