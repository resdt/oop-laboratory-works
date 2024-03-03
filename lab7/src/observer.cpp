#include <observer.h>

#include <iostream>
#include "npc.h"

print::~print() {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lck(mtx);
    std::cout << this->str();
    std::cout.flush();
}

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker,
                            const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        print() << std::endl << "Fight --------" << std::endl;
        attacker->print();
        defender->print();
    }
}