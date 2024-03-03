#include "factory.h"
#include "npc.h"
#include "bear.h"
#include "elf_.h"
#include "rogue.h"

std::shared_ptr<NPC> factory(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
            case static_cast<int>(NpcType::BearType):
                result = std::make_shared<Bear>(is);
                break;
            case static_cast<int>(NpcType::ElfType):
                result = std::make_shared<Elf>(is);
                break;
            case static_cast<int>(NpcType::RogueType):
                result = std::make_shared<Rogue>(is);
                break;
        }
    } else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result) {
        result->subscribe(TextObserver::get());
    };

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
        case (NpcType::BearType):
            result = std::make_shared<Bear>(x, y);
            break;
        case (NpcType::ElfType):
            result = std::make_shared<Elf>(x, y);
            break;
        case (NpcType::RogueType):
            result = std::make_shared<Rogue>(x, y);
            break;
        default:
            break;
    }
    if (result) result->subscribe(TextObserver::get());

    return result;
}