#include "observer.h"

#include <iostream>

#include "npc.h"

TextObserver::TextObserver(){};
std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker,
                            const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        std::cout << std::endl << "Murder ---------------" << std::endl;
        attacker->print(std::cout);
        defender->print(std::cout);
    }
}

FileObserver::FileObserver(const std::string &filename) : file(filename){};
std::shared_ptr<IFightObserver> FileObserver::get() {
    static FileObserver instance("log.txt");
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

void FileObserver::on_fight(const std::shared_ptr<NPC> attacker,
                            const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        file << std::endl << "Murder ---------------" << std::endl;
        attacker->print(file);
        defender->print(file);
    }
}