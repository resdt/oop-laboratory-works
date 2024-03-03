#pragma once

#include <memory>

struct NPC;
enum class NpcType;

std::shared_ptr<NPC> factory(std::istream &is);
std::shared_ptr<NPC> factory(NpcType type, int x, int y,
                             const std::string &name);