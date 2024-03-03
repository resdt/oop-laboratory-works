#include "visitor.h"
#include "npc.h"

FightVisitor::FightVisitor(std::shared_ptr<NPC> attacker) : attacker(attacker) {}

bool FightVisitor::visit(std::shared_ptr<Bear> element) {
    return attacker->fight(element);
}
bool FightVisitor::visit(std::shared_ptr<Elf> element) {
    return attacker->fight(element);
}
bool FightVisitor::visit(std::shared_ptr<Rogue> element) {
    return attacker->fight(element);
}