#pragma once
#include <memory>
#include <sstream>

struct NPC;

struct print : std::stringstream {
    ~print(); 
};


struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker,
                          const std::shared_ptr<NPC> defender, bool win) = 0;
    virtual ~IFightObserver() = default;
};

class TextObserver : public IFightObserver {
   private:
    TextObserver() = default;

   public:
    static std::shared_ptr<IFightObserver> get();
    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override;
};