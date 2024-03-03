#pragma once
#include <memory>

struct NPC;
struct Bear;
struct Elf;
struct Rogue;

class Visitor {
   public:
    virtual bool visit(std::shared_ptr<Bear> element) = 0;
    virtual bool visit(std::shared_ptr<Elf> element) = 0;
    virtual bool visit(std::shared_ptr<Rogue> element) = 0;
    virtual ~Visitor() = default;
};

class FightVisitor : public Visitor {
   public:
    FightVisitor(std::shared_ptr<NPC>);
    bool visit(std::shared_ptr<Bear> element) override;
    bool visit(std::shared_ptr<Elf> element) override;
    bool visit(std::shared_ptr<Rogue> element) override;

   private:
    std::shared_ptr<NPC> attacker;
};


