#include "elf_.h"

#include "bear.h"
#include "rogue.h"

Elf::Elf(int x, int y) : NPC(NpcType::ElfType, x, y) {}
Elf::Elf(std::istream &is) : NPC(NpcType::ElfType, is) {}

bool Elf::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Elf>(this, [](Elf *) {}));
}

void Elf::print() { std::cout << *this; }

bool Elf::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

bool Elf::fight(std::shared_ptr<Rogue> other) {
    fight_notify(other, true);
    return true;
}

bool Elf::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false);
    return false;
}

void Elf::save(std::ostream &os) {
    os << static_cast<int>(NpcType::ElfType) << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Elf &elf) {
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}

bool Elf::is_close(const std::shared_ptr<NPC> &other) { return NPC::is_close(other, 50); }

int Elf::get_move_distance() {
    return 10;
}